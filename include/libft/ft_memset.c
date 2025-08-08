/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:24:17 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/14 22:38:47 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) b;
	while (len)
	{
		*ptr = c;
		len--;
		ptr++;
	}
	return (b);
}
// takes a pointer to a memory block b,
// fills first len byte spots with value at c
// return pointer to the original memory adress
// RAW memory function, used to reset spots no matter what

// void pointer needs to be cast or it has no clue how many bytes to read
// pointer arithmetic depends on pointer type (int = 4)
// cast to unsigned char cuz it's only 1 byte
//#include <stddef.h>
// int main(void)
// {
	// 	char buffer[20] = "Hello, World!";
	// 	printf("Before memset: %s\n", buffer);
	// 	ft_memset(buffer, 'A', 5);  // Fill first 5 bytes with 'A'
	// 	printf("After memset: %s\n", buffer);  // Expected: "AAAAAo, World!"
	// 	return 0;
	// }