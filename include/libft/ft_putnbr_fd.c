/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:44:56 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/19 02:07:06 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	buffer[12];
	int		i;

	nbr = n;
	if (nbr == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	i = 0;
	while (nbr > 0)
	{
		buffer[i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	while (i-- > 0)
		ft_putchar_fd(buffer[i], fd);
}
