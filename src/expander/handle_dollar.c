/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:55:02 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/03 22:31:23 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar(t_shell *sh, t_token *t, char *str, t_exp *exp)
{
	if (str[exp->i + 1] == '?')
	{
		handle_error(t, exp, sh);
	}
	else if (is_valid_var_start(str[exp->i + 1]))
	{
		if (expand_var(sh, t, str, exp) < 0)
			return (-1);
	}
	else
		handle_char(t, str, exp);
	return (0);
}

void	handle_error(t_token *t, t_exp *exp, t_shell *sh)
{
	size_t	written;

	exp->in_exp = true;
	written = write_exit_code(t->value + exp->j, sh->last_exit_code);
	while (written--)
	{
		t->context[exp->j] = get_context(exp->in_sq, exp->in_dq, exp->in_exp);
		exp->j++;
	}
	exp->i += 2;
	exp->in_exp = false;
}

int	expand_var(t_shell *sh, t_token *t, char *str, t_exp *exp)
{
	char	*varname;
	char	*temp;
	size_t	k;

	exp->i++;
	varname = extract_varname(sh, str, &exp->i);
	if (!varname)
		return (-1);
	temp = get_env_value(sh, varname);
	if (!temp)
		temp = "";
	exp->in_exp = true;
	k = 0;
	while (temp[k])
	{
		t->context[exp->j] = get_context(exp->in_sq, exp->in_dq, exp->in_exp);
		t->value[exp->j++] = temp[k++];
	}
	exp->in_exp = false;
	return (0);
}
