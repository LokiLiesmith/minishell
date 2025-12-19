/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 00:58:43 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/04 00:58:52 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_delim(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	handle_delims(char *str, char *context, int i)
{
	if ((context[i] == '0' || context[i] == 'e') && ft_is_delim(str[i]))
	{
		while (str[i] && (context[i] == '0' || context[i] == 'e')
			&& ft_is_delim(str[i]))
			i++;
		return (0);
	}
	return (-1);
}

static int	handle_operator(char *str, char *context, int i)
{
	if ((context[i] == '0' || context[i] == 'e') && is_operator(str[i]))
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (2);
		if (str[i] == '<' && str[i + 1] == '<')
			return (2);
		return (1);
	}
	return (-1);
}

int	ctx_split_len(char *str, char *context, int i)
{
	int	len;
	int	res;

	if (!str || !str[i])
		return (0);
	res = handle_delims(str, context, i);
	if (res >= 0)
		return (res);
	res = handle_operator(str, context, i);
	if (res >= 0)
		return (res);
	len = 0;
	while (str[i + len])
	{
		if ((context[i + len] == '0' || context[i + len] == 'e'))
		{
			if (ft_is_delim(str[i + len]) || is_operator(str[i + len]))
				break ;
		}
		len++;
	}
	return (len);
}
