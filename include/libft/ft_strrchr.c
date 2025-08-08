/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:29:04 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/15 14:54:58 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*end;

	end = s;
	while (*end)
		end++;
	while (end >= s)
	{
		if (*end == (char)c)
			return ((char *)end);
		end--;
	}
	return (NULL);
}

/* #include <stdio.h>

void test_ft_strrchr(const char *str, int c)
{
    char *result = ft_strrchr(str, c);
    if (result)
        printf("Srchn last '%c' in \"%s\": Fnd at \"%s\"\n", c, str, result);
    else
        printf("Searching last '%c' in \"%s\": Not found.\n", c, str);
}

int main(void)
{
    test_ft_strrchr("Hello, world!", 'o');  // Expected: "orld!"
    test_ft_strrchr("42 Network 42", '4');  // Expected: "42" (last one)
    test_ft_strrchr("Hello, world!", 'z');  // Expected: Not found.
    test_ft_strrchr("Hello, world!", '\0'); // Expected: "" (pointer to '\0')

    return 0;
}
 */