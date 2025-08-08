/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:14:43 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/16 18:33:23 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;

	copy = (char *)malloc(ft_strlen(s) +1);
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

/* void	test_ft_strdup(const char *s)
{
	char	*copy;

	copy = ft_strdup(s);
	printf("Original: %s -> Copy: %s\n", s, copy);
	free(copy);
}

int	main(void)
{
	test_ft_strdup("eyo, 420!");
	test_ft_strdup("");
	test_ft_strdup("Malloc test!420!");
	return (0);
}
 */