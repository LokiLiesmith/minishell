/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:24:31 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/22 12:45:55 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isalnum('A'));
// 	printf("%d\n", ft_isalnum('}'));
// 	printf("%d\n", ft_isalnum('a'));
// 	printf("%d\n", ft_isalnum('9'));
// 	return (0);
// }