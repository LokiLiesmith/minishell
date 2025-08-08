/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:24:07 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/15 23:36:40 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

/* void	test_ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	result;

	result = ft_strncmp(s1, s2, n);
	printf("Comparing: \"%s\" and \"%s\" (n = %zu): %d\n", s1, s2, n, result);
}

int	main(void)
{
	test_ft_strncmp("apple", "apricot", 3);
	test_ft_strncmp("apple", "banana", 5);
	test_ft_strncmp("hello", "hella", 5);
	test_ft_strncmp("hello", "hell", 10);
	test_ft_strncmp("test", "test", 4);
	return (0);
}
 */