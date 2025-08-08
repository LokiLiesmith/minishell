/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:35:20 by mrazem            #+#    #+#             */
/*   Updated: 2025/04/06 15:40:27 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printunsigned(unsigned int n)
{
	char	buffer[10];
	int		i;

	i = 0;
	if (n == 0)
		return (ft_safe_write(1, "0", 1));
	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i-- > 0)
	{
		if (ft_safe_write(1, &buffer[i], 1) == -1)
			return (-1);
	}
	return (0);
}
