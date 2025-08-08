/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:14:52 by mrazem            #+#    #+#             */
/*   Updated: 2025/04/06 15:14:58 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_safe_write(int fd, const void *buf, size_t count)
{
	ssize_t	written;

	written = write(fd, buf, count);
	if (written == -1)
		return (-1);
	return (ft_printed(written));
}
