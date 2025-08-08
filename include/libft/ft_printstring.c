/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:15:07 by mrazem            #+#    #+#             */
/*   Updated: 2025/04/06 15:14:44 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstring(char *passed_string)
{
	int	w;

	w = 0;
	if (!passed_string)
		passed_string = "(null)";
	while (*passed_string)
	{
		w = ft_safe_write(1, passed_string, 1);
		if (w == -1)
			return (-1);
		passed_string++;
	}
	return (0);
}
