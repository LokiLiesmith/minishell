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
t_token	*token_create(t_shell *sh, t_token_type type, char *start, int len)
{
	t_token	*new;

	new = gc_malloc(sh, sizeof(t_token), GC_TEMP);
	new->type = type;
	new->raw = malloc(sh, (sizeof(char) * len + 1), GC_TEMP);
	ft_memcpy(new->raw, start, len);
	new->raw[len] = '\0';
	new->value = NULL;
	new->context = NULL;
	new->next = NULL;
	new->was_expanded = false;
	return (new);
}

void	token_append(t_token **head, t_token **tail, t_token *new)
{
	if (!new)
		return ;
	if (head == NULL)
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

static void	init_lexer(t_lexer *lex)
{
	lex->len = 0;
	lex->op = WORD;
	lex->i = 0;
	lex->head = NULL;
	lex->tail = NULL;
}

static int	handle_operator(t_lexer *lex, char *str)
{
	t_token	*new;

	lex->len = scan_operator(str, lex->i, &lex->op);
	if (lex->len <= 0)
		return (0);
	new = token_create(sh, lex->op, str + lex->i, lex->len);
	token_append(&lex->head, &lex->tail, new);
	lex->i += lex->len;
	return (1);
}

//word handler (if scan_word < 0; => open quotes)
static int	handle_word(t_lexer *lex, char *str, bool *open_quotes)
{
	t_token	*new;

	lex->len = scan_word(str, lex->i);
	if (lex->len < 0)
	{
		if (open_quotes) // so they can be NULL, used in main
			*open_quotes = true;
		return (0);
	}
	new = token_create(sh, WORD, str + lex->i, lex->len);
	token_append(&lex->head, &lex->tail, new);
	lex->i += lex->len;
	return (1);
}

// void free_tokens(t_token *token)
// {
// 	t_token *temp;
	
// 	while (token)
// 	{
// 		temp = token->next;
// 		if (token->value)
// 			free(token->value);
// 		if (token->raw)
// 			free(token->raw);
// 		if (token->context)
// 			free(token->context);
// 		free(token);
// 		token = temp;
// 	}
// }

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



