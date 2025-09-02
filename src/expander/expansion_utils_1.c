/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:36:27 by mrazem            #+#    #+#             */
/*   Updated: 2025/09/01 20:36:29 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exp_struct(t_exp *exp)
{
	exp->i = 0;
	exp->j = 0;
	// exp->k = 0;
	exp->count = 0;
	exp->in_sq = false;
	exp->in_dq = false;
}

void	update_quotes(char c, bool *in_sq, bool *in_dq)
{
	if (!*in_dq && c == '\'')
		*in_sq = !*in_sq;
	else if (!*in_sq && c == '"')
		*in_dq = !*in_dq;
}

int	calc_quotes(bool in_sq, bool in_dq)
{
	if (in_dq)
		return (2);
	else if (in_sq)
		return (1);
	return (0);
}

void	increment_counters(int *i, int *b)
{
	(*i)++;
	(*b)++;
}
