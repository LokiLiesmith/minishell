/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:54:10 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/14 22:39:18 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// unsigned int type and const char so it's read only and it cant rewrite
//look for NULL char and increment
// size_t - unsigned integer type for sizes and lenghts dealing with memory 
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
// int main(void)
// {
// 	char *string = "ThisisAtest!";
// 	printf("String: %s\n", string);
// 	printf("Length of string: %zu\n", ft_strlen(string));
// 	return(0);
// }
