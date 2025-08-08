/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:47:33 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/20 20:36:22 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substring = (char *) malloc (len +1);
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}
/* #include <stdio.h>

void test_ft_substr(const char *s, unsigned int start, size_t len)
{
    char *sub = ft_substr(s, start, len);
    printf("ft_substr(\"%s\", %u, %zu) -> \"%s\"\n", s, start, len, sub);
    free(sub);
}

int main(void)
{
    test_ft_substr("Hello, World!", 7, 5);
    test_ft_substr("Hello, World!", 0, 5);
    test_ft_substr("Hello", 5, 3);
    test_ft_substr("Hello", 10, 3);         
    test_ft_substr("42", 1, 10);            
    test_ft_substr("42", 0, 0);             

    return 0;
} */