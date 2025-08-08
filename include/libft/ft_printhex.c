/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:53:10 by mrazem            #+#    #+#             */
/*   Updated: 2025/04/06 15:14:25 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhex(unsigned int n, int is_uppercase)
{
	int		i;
	int		remainders[20];
	char	*hex_digits;

	i = 0;
	if (n == 0)
		return (ft_safe_write(1, "0", 1));
	if (is_uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	while (n > 0)
	{
		remainders[i++] = n % 16;
		n /= 16;
	}
	while (--i >= 0)
	{
		if (ft_safe_write(1, &hex_digits[remainders[i]], 1) == -1)
			return (-1);
	}
	return (0);
}
