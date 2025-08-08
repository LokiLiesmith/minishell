/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:57:04 by mrazem            #+#    #+#             */
/*   Updated: 2025/03/17 00:12:28 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	total_length;

	total_length = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = malloc(total_length);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, total_length);
	ft_strlcat(new_str, s2, total_length);
	return (new_str);
}
