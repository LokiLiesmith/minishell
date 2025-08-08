/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:32:57 by mrazem            #+#    #+#             */
/*   Updated: 2025/04/06 15:13:52 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_printed(int increment)
{
	static size_t	n = 0;

	if (increment == -1)
		return (n = 0);
	return (n += increment);
}
/* int main (void)
{
	printf("%zu", ft_printed(1));
	printf("%zu", ft_printed(1));
	printf("%zu", ft_printed(1));
	printf("%zu", ft_printed(1));
	printf("%zu", ft_printed(1));
	printf("%zu", ft_printed(1));
	printf("%zu", ft_printed(0));



	return (0);
} */