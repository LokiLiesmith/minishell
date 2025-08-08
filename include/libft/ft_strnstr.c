/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:21:23 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/15 23:36:37 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			while (haystack [i + j] == needle[j] && (i + j) < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)&haystack[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
/* #include <stdio.h>
#include <string.h>

void test_ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    char *result = ft_strnstr(haystack, needle, len);
    printf("Searching \"%s\" in \"%s\" (len = %zu): %s\n",
           needle, haystack, len, result ? result : "Not found");
}

int main(void)
{
    test_ft_strnstr("42 school is amazing!", "school", 12);  // 
    test_ft_strnstr("42 school is amazing!", "is", 10);      // 
    test_ft_strnstr("42 school is amazing!", "cool", 10);    // 
    test_ft_strnstr("42 school", "", 10);                    // 
    return 0;
}
 */