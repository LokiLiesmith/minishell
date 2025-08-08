/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:57:43 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/15 23:36:39 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* strlcat() appends string src to the end of dst.  It will append at most
dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
dstsize is 0 or the original dst string was longer than dstsize (in prac-
tice this should not happen as it means that either dstsize is incorrect
or that dst is not a proper string).

If the src and dst strings overlap, the behavior is undefined.

Like snprintf(3), the strlcpy() and strlcat() functions return the total
     length of the string they tried to create.  For strlcpy() that means the
     length of src.  For strlcat() that means the initial length of dst plus
     the length of src.

     If the return value is >= dstsize, the output string has been truncated.
     It is the caller's responsibility to handle this.
 */

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	available_space;

	dst_len = 0;
	src_len = 0;
	i = 0;
	while (dst_len < dstsize && dst[dst_len])
		dst_len++;
	while (src[src_len])
		src_len++;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	available_space = dstsize - dst_len - 1;
	while (i < available_space && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (available_space > 0)
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
