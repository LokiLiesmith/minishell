/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:32:26 by mrazem            #+#    #+#             */
/*   Updated: 2025/04/06 15:14:38 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printptr(void *ptr)
{
	uintptr_t			address;
	int					i;
	int					remainders[20];
	char				*hex_digits;

	i = 0;
	hex_digits = "0123456789abcdef";
	address = (uintptr_t)ptr;
	if (ft_safe_write(1, "0x", 2) == -1)
		return (-1);
	if (address == 0)
		return (ft_safe_write(1, "0", 1));
	while (address > 0)
	{
		remainders[i++] = address % 16;
		address /= 16;
	}
	while (--i >= 0)
	{
		if (ft_safe_write(1, &hex_digits[remainders[i]], 1) == -1)
			return (-1);
	}
	return (0);
}
