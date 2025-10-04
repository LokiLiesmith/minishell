/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:36:27 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/03 22:12:57 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exp_struct(t_exp *exp)
{
	exp->i = 0;
	exp->j = 0;
	exp->k = 0;
	exp->count = 0;
	exp->in_sq = false;
	exp->in_dq = false;
	exp->in_exp = false;
}

void	update_quotes(char c, bool *in_sq, bool *in_dq)
{
	if (!*in_dq && c == '\'')
		*in_sq = !*in_sq;
	else if (!*in_sq && c == '"')
		*in_dq = !*in_dq;
}

char	get_context(bool in_sq, bool in_dq, bool in_exp)
{
	if (in_dq)
		return ('d');
	else if (in_sq)
		return ('s');
	else if (in_exp)
		return ('e');
	return ('0');
}

void	increment_counters(int *i, int *b)
{
	(*i)++;
	(*b)++;
}

char	*get_env_value(t_shell *sh, char *varname)
{
	t_env	*env;

	env = sh->env;
	while (env)
	{
		if (ft_strcmp(env->type, varname) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
