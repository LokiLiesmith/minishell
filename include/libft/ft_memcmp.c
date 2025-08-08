/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:19:11 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/14 17:45:14 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NAME
//      memcmp -- compare byte string
// LIBRARY
//      Standard C Library (libc, -lc)
// SYNOPSIS
//      #include <string.h>
//      int
//      memcmp(const void *s1, const void *s2, size_t n);
// DESCRIPTION
//      The memcmp() function compares byte string s1 against byte string s2.
//      Both strings are assumed to be n bytes long.
// RETURN VALUES
//      The memcmp() function returns zero if the two strings are idntcl, oth-
//      erwise returns the difference between the first two differing bytes
//      (treated as unsigned char values, so that `\200' is greater than `\0',
//      for example).  Zero-length strings are always identical.  This behavior
//      is not required by C and portable code should only depend on the sign of
//      the returned value.
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return ((ptr1[i] - ptr2[i]));
		i++;
	}
	return (0);
}
