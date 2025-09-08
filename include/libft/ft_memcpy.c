/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:38:45 by mrazem            #+#    #+#             */
/*   Updated: 2025/09/08 17:36:51 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//copy n bytes from memory src to memory dst
//
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!dst && !src && n > 0)
// 		return (NULL);
// 	while (i < n)
// 	{
// 		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
// 		i++;
// 	}
// 	return (dst);
// } void pointer arithmetic!!
