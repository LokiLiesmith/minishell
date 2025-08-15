/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:04:13 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/15 21:23:30 by mrazem           ###   ########.fr       */
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
void push_token(t_token **head,t_token **tail, t_token_type type, char *start, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->value = malloc(sizeof(char) * len + 1);
	if (!new->value)
		return ;
	ft_memcpy(new->value, start, len);
	new->value[len] = '\0';
	new->next = NULL;
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
	lex->word_len = 0;
}
// static void	print_lexer(t_lexer *lex)
// {
// 	printf("token value %s\n", lex->tail->value);
// 	printf("lex->len: %zd\n", lex->len);
// 	printf("lex->op: %d\n", lex->op);
// 	printf("lex->i: %d\n", lex->i);
// 	printf("lex->head: %p\n", lex->head);
// 	printf("lex->tail: %p\n", lex->tail);
// }

t_token	*tokenize(char *str)
{
	t_lexer	lex;

	init_lexer(&lex);
	while (str[lex.i])
	{
		while (ft_is_space(str[lex.i])) //skip whitespace
			lex.i++;
		lex.len = scan_operator(str, lex.i, &lex.op);
		if (lex.len > 0) //is operator
		{
			push_token(&lex.head, &lex.tail, lex.op, str + lex.i, lex.len);
			lex.i += lex.len;
			continue ;
		}
		lex.word_len = scan_word(str, lex.i);
		if (lex.word_len >= 0)
		{
			push_token(&lex.head, &lex.tail, WORD, str + lex.i, lex.word_len);
			lex.i += lex.word_len;
		}
		if (lex.word_len < 0)//NEGATIVE from scan word == open quotes
			return NULL;
	}
	return (lex.head);
}
