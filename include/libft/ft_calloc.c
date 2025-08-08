/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:53:23 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/16 19:51:15 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* figure out how much space you need (count x size)
allocate using 	empty = (char *)malloc(count * size);
if (!empty)
	return (NULL);
set memory to zero using ft_bzero

return pointer to the start of the allocated memory
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*empty;

	empty = malloc(count * size);
	if (!empty)
		return (NULL);
	ft_bzero(empty, count * size);
	return (empty);
}
/* void test_ft_calloc(size_t count, size_t size)
{
	int
} */