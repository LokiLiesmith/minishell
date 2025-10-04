/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_strip.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:21:17 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/03 22:30:54 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_and_strip(t_shell *sh, t_token *t, int exp_len)
{
	t_exp	exp;
	char	*str;

	t->value = gc_calloc(sh, exp_len + 1, sizeof(char), GC_TEMP);
	t->context = gc_calloc(sh, exp_len + 2, sizeof(char), GC_TEMP);
	if (!t->value || !t->context)
		return (-1);
	str = t->raw;
	init_exp_struct(&exp);
	while (str[exp.i])
	{
		if (str[exp.i] == '\'' || str[exp.i] == '"')
			handle_quote(t, str, &exp);
		else if (!exp.in_sq && str[exp.i] == '$')
		{
			if (handle_dollar(sh, t, str, &exp) < 0)
				return (-1);
		}
		else
			handle_char(t, str, &exp);
	}
	t->value[exp.j] = '\0';
	t->context[exp.j] = '\0';
	tag_quoted_empty(t);
	return (0);
}

void	handle_quote(t_token *t, const char *str, t_exp *exp)
{
	char	c;

	c = str[exp->i];
	if ((c == '\'' && !exp->in_dq) || (c == '"' && !exp->in_sq))
	{
		update_quotes(str[exp->i], &exp->in_sq, &exp->in_dq);
		exp->i++;
	}
	else
	{
		t->context[exp->j] = get_context(exp->in_sq, exp->in_dq, exp->in_exp);
		t->value[exp->j++] = str[exp->i++];
	}
}

void	handle_char(t_token *t, char *str, t_exp *exp)
{
	t->context[exp->j] = get_context(exp->in_sq, exp->in_dq, exp->in_exp);
	t->value[exp->j++] = str[exp->i++];
}

//empty token "" case
void	tag_quoted_empty(t_token *t)
{
	if (!t || !t->raw)
		return ;
	if (t->value[0] == '\0')
	{
		if (ft_strchr(t->raw, '"'))
			strcpy(t->context, "d");
		else if (ft_strchr(t->raw, '\''))
			strcpy(t->context, "s");
	}
}
