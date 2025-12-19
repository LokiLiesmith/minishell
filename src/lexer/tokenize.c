/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:04:13 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/03 23:47:12 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_lexer(t_lexer *lex)
{
	lex->len = 0;
	lex->op = WORD;
	lex->i = 0;
	lex->head = NULL;
	lex->tail = NULL;
}

static int	handle_operator(t_shell *sh, t_lexer *lex, char *str)
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
static int	handle_word(t_shell *sh, t_lexer *lex, char *str, bool *open_quotes)
{
	t_token	*new;

	lex->len = scan_word(str, lex->i);
	if (lex->len < 0)
	{
		if (open_quotes)
			*open_quotes = true;
		return (0);
	}
	new = token_create(sh, WORD, str + lex->i, lex->len);
	token_append(&lex->head, &lex->tail, new);
	lex->i += lex->len;
	return (1);
}

t_token	*tokenize(t_shell *sh, char *str, bool *open_quotes)
{
	t_lexer	lex;

	init_lexer(&lex);
	if (open_quotes)
		*open_quotes = false;
	while (str[lex.i])
	{
		while (ft_is_space(str[lex.i]))
			lex.i++;
		if (handle_operator(sh, &lex, str))
			continue ;
		if (!handle_word(sh, &lex, str, open_quotes))
			return (NULL);
	}
	return (lex.head);
}
