/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:36:17 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/03 21:36:45 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	write_exit_code(char *dst, int last_exit_code)
{
	char	buffer[12];
	long	num;
	size_t	len;
	size_t	i;
	bool	neg;

	num = last_exit_code;
	neg = num < 0;
	if (neg)
		num = -num;
	len = 0;
	if (num == 0)
		buffer[len++] = '0';
	while (num > 0)
	{
		buffer[len++] = '0' + (num % 10);
		num /= 10;
	}
	i = 0;
	if (neg)
		dst[i++] = '-';
	while (len > 0)
		dst[i++] = buffer[--len];
	return (i);
}
