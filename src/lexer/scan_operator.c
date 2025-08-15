/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:03:20 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/15 21:06:56 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_less_than(const char *str, int i, t_token_type *type)
{
	if (str[i + 1] == '<')
	{
		*type = T_HEREDOC;
		return (2);
	}
	*type = T_IN;
	return (1);
}

static int	handle_more_than(const char *str, int i, t_token_type *type)
{
	if (str[i + 1] == '>')
	{
		*type = T_APPEND;
		return (2);
	}
	*type = T_OUT;
	return (1);
}

ssize_t	scan_operator(const char *str, int i, t_token_type *type)
{
	if (str[i] == '|')
	{
		*type = PIPE;
		return (1);
	}
	else if (str[i] == '<')
		return (handle_less_than(str, i, type));
	else if (str[i] == '>')
		return (handle_more_than(str, i, type));
	return (0);
}