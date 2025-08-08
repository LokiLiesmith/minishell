/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:56:11 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/22 13:11:38 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/* //TESTERFUNK
// cc -Werror -Wextra -Wall ft_striteri.c ft_isalpha.c -o striteri
#include <stdio.h>

void ft_even_to_upper(unsigned int i, char *c)
{
	if (i % 2 == 0 && ft_isalpha(*c))
		*c -= 32;
}

int main (void)
{
	char str1[] = "eyo, this is a test.";
	printf("Original: %s\n", str1);
	ft_striteri(str1, ft_even_to_upper);
	printf("Funkedup: %s\n\n", str1);
	
	char empty[] = "";
	printf("Empty: %s\n", str1);
	ft_striteri(str1, ft_even_to_upper);
	printf("Funkedup: %s\n\n", empty);
	
	char safe[] = "safe";
	printf("No funk: %s\n", safe);
	ft_striteri(str1, ft_even_to_upper);
	printf("Funkedup: %s\n\n", safe);
	
	printf("NULLstr:\n");
	ft_striteri(NULL, ft_even_to_upper);
	printf("Didn't crash.\n\n");
	
}
 */