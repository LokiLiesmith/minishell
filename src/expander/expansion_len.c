/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:04:13 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/03 23:31:33 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote_len(const char *str, t_exp *exp);
static int	handle_dollar_len(t_shell *sh, char *str, t_exp *exp);
static int	handle_var_expansion_len(t_shell *sh, char *str, t_exp *exp);

int	expansion_len(t_shell *sh, char *str)
{
	t_exp	exp;

	init_exp_struct(&exp);
	while (str[exp.i])
	{
		if (str[exp.i] == '\'' || str[exp.i] == '"')
			handle_quote_len(str, &exp);
		else if (!exp.in_sq && str[exp.i] == '$')
		{
			if (handle_dollar_len(sh, str, &exp) < 0)
				return (-1);
		}
		else
			increment_counters(&exp.i, &exp.count);
	}
	return (exp.count);
}

static void	handle_quote_len(const char *str, t_exp *exp)
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
		exp->i++;
		exp->count++;
	}
}

static int	handle_dollar_len(t_shell *sh, char *str, t_exp *exp)
{
	if (str[exp->i + 1] == '?')
	{
		exp->count += get_error_len(sh->last_exit_code);
		exp->i += 2;
		return (0);
	}
	else if (is_valid_var_start(str[exp->i + 1]))
		return (handle_var_expansion_len(sh, str, exp));
	exp->i++;
	exp->count++;
	return (0);
}

static int	handle_var_expansion_len(t_shell *sh, char *str, t_exp *exp)
{
	char	*varname;
	char	*temp;
	int		var_len;

	exp->i++;
	varname = extract_varname(sh, str, &exp->i);
	if (!varname)
		return (-1);
	temp = get_env_value(sh, varname);
	if (!temp)
		temp = "";
	var_len = ft_strlen(temp);
	exp->count += var_len;
	return (0);
}
