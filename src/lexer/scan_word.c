/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:59:23 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/15 21:23:31 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_operator(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	ft_is_space(int c)
{
	return ((c == '\t') || c == ' ');
}

// return len of the word
ssize_t	scan_word(const char *str, size_t i)
{
	int	start;
	int	in_double_q;
	int	in_single_q;

	start = i;
	in_single_q = 0;
	in_double_q = 0;
	while (str[i])
	{
		if (!in_double_q && str[i] == '\'')
			in_single_q = !in_single_q;
		else if (!in_single_q && str[i] == '"')
			in_double_q = !in_double_q;
		else if (!in_single_q && !in_double_q)
		{
			if (ft_is_space((unsigned char)str[i]) || ft_is_operator(str[i]))
				break ;
		}
		i++;
	}
	if (in_single_q || in_double_q)
		return (-1);
	return (ssize_t)(i - start);
}
