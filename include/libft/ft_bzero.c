/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:25:53 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/12 23:26:02 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// take a pointer and fill the next n bytes with 0.
// Cast void pointer to unsigned char so it knows what datatype,
// and how to do the pointer arithmetic 
// change the next n bytes to 0 while n larger than 0.
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n)
	{
		*ptr++ = 0;
		n--;
	}
}
