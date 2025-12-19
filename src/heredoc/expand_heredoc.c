/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 23:09:52 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/03 23:43:30 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exit_code(t_shell *sh, t_exp *exp, char *out, char *str)
{
	exp->j += write_exit_code(out + exp->j, sh->last_exit_code);
	exp->i += 2;
	(void)str;
}

void	handle_var_expand(t_shell *sh, t_exp *exp, char *out, char *str)
{
	char	*varname;
	char	*value;

	exp->i++;
	varname = extract_varname(sh, str, &exp->i);
	value = get_env_value(sh, varname);
	if (!value)
		value = "";
	while (*value)
		out[exp->j++] = *value++;
}

char	*expand_string(t_shell *sh, char *str)
{
	t_exp	exp;
	int		new_len;
	char	*out;

	if (!str)
		return (NULL);
	init_exp_struct(&exp);
	new_len = hdoc_len(sh, str);
	out = gc_malloc(sh, new_len + 1, GC_TEMP);
	while (str[exp.i])
	{
		if (str[exp.i] == '$' && str[exp.i + 1] == '?')
			handle_exit_code(sh, &exp, out, str);
		else if (str[exp.i] == '$' && is_valid_var_start(str[exp.i + 1]))
			handle_var_expand(sh, &exp, out, str);
		else
			out[exp.j++] = str[exp.i++];
	}
	out[exp.j] = '\0';
	return (out);
}

char	*expand_heredoc(t_shell *sh, t_redir *r, char *line)
{
	char	*expanded;

	if (!line)
		return (NULL);
	if (r->heredoc_quoted)
		expanded = gc_strdup(sh, line, GC_TEMP);
	else
		expanded = expand_string(sh, line);
	free(line);
	return (expanded);
}
