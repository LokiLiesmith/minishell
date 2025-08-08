/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:24:57 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/14 22:48:19 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* If the argument is a lower-case letter, the toupper() function returns
the corresponding upper-case letter if there is one; otherwise, the argu-
ment is returned unchanged.
 */
#include "libft.h"

int	ft_toupper(int c)
{
	if (c <= 122 && c >= 97)
		return (c - 32);
	return (c);
}
