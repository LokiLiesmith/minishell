/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:22:21 by mrazem            #+#    #+#             */
/*   Updated: 2025/04/06 15:14:31 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnum(int n, int fd)
{
	char	buffer[12];
	int		i;
	long	nbr;

	nbr = n;
	i = 0;
	if (nbr == 0)
		return (ft_safe_write(fd, "0", 1));
	if (nbr < 0)
	{
		if (ft_safe_write(fd, "-", 1) == -1)
			return (-1);
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		buffer[i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	while (i-- > 0)
	{
		if (ft_safe_write(fd, &buffer[i], 1) == -1)
			return (-1);
	}
	return (0);
}
