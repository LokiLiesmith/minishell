/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:52:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/18 14:21:12 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}

/* #include <stdio.h>

void test_ft_atoi(const char *str)
{
    printf("Input: \"%s\" -> Output: %d\n", str, ft_atoi(str));
}

int main(void)
{
    test_ft_atoi("42");          // Expected: 42
    test_ft_atoi("   -123abc");  // Expected: -123
    test_ft_atoi("+99");         // Expected: 99
    test_ft_atoi("words 56");    // Expected: 0
    test_ft_atoi("+-420");    // Expected: 
    test_ft_atoi("-+420");    // Expected: 
    test_ft_atoi("");            // Expected: 0
    return 0;
}
 */