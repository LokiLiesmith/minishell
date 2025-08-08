/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:17:23 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/20 20:29:06 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// The strlcpy() and strlcat() functions copy and concatenate strings with
// the same input parameters and output result as snprintf(3).  They are
// designed to be safer, more consistent, and less error prone replacements
// for the easily misused functions strncpy(3) and strncat(3).
// strlcpy() and strlcat() take the full size of the destination buffer and
// guarantee NUL-termination if there is room.  Note that room for the NUL
// should be included in dstsize.
// strlcpy() copies up to dstsize - 1 characters from the string src to dst,
// NUL-terminating the result if dstsize is not 0.

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	if (dstsize > 0)
	{
		while ((i < dstsize - 1) && (src[i] != '\0'))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}
