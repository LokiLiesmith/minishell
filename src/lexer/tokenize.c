/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:04:13 by mrazem            #+#    #+#             */
/*   Updated: 2025/09/09 02:04:09 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////////////////////////////////////////////////////////////////////////////
//							TOKENIZE?										  //
////////////////////////////////////////////////////////////////////////////////
// TOKENIZE LOOP
// skip whitespace
// if operator(push_token based on operator)
// else its a word, and push_token with len of the word and the string
void push_token(t_token **head, t_token **tail, t_token_type type, char *start, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->raw = malloc(sizeof(char) * len + 1);
	if (!new->raw)
		return ;
	ft_memcpy(new->raw, start, len);
	new->raw[len] = '\0';
	new->value = NULL;
	new->context = NULL;
	new->next = NULL;
	new->was_expanded = false;
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

static void init_lexer(t_lexer *lex)
{
	lex->len = 0;
	lex->op = WORD;
	lex->i = 0;
	lex->head = NULL;
	lex->tail = NULL;
}

static int	handle_operator(t_lexer *lex, char *str)
{
	lex->len = scan_operator(str, lex->i, &lex->op);
	if (lex->len <= 0)
		return (0);
	push_token(&lex->head, &lex->tail, lex->op, str + lex->i, lex->len);
	lex->i += lex->len;
	return (1);
}

//word handler (if scan_word < 0; => open quotes)
static int	handle_word(t_lexer *lex, char *str, bool *open_quotes)
{
	lex->len = scan_word(str, lex->i);
	if (lex->len < 0)
	{
		if (open_quotes) // so they can be NULL, used in main
			*open_quotes = true;
		return (0);
	}
	push_token(&lex->head, &lex->tail, WORD, str + lex->i, lex->len);
	lex->i += lex->len;
	return (1);
}

void free_tokens(t_token *token)
{
	t_token *temp;
	
	while (token)
	{
		temp = token->next;
		if (token->value)
			free(token->value);
		if (token->raw)
			free(token->raw);
		if (token->context)
			free(token->context);
		free(token);
		token = temp;
	}
}

t_token *tokenize(char *str, bool *open_quotes)
{
	t_lexer	lex;

	init_lexer(&lex);
	if (open_quotes)
		*open_quotes = false;
	while (str[lex.i])
	{
		while (ft_is_space(str[lex.i]))
			lex.i++;
		if (handle_operator(&lex, str))
			continue ;
		if (!handle_word(&lex, str, open_quotes))
			return (NULL);
	}
	return (lex.head);
}

