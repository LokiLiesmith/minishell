/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:20:45 by msalangi          #+#    #+#             */
/*   Updated: 2025/08/09 22:25:23 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"

void	ft_save_buffer(char *curr_buffer, char *buffer)
{
	char	*newline;
	size_t	count;

	count = 0;
	newline = ft_strrchr(curr_buffer, '\n');
	if (!newline)
	{
		buffer[0] = '\0';
		return ;
	}
	newline++;
	while (newline[count] && count < BUFFER_SIZE)
	{
		buffer[count] = newline[count];
		count++;
	}
	buffer[count] = '\0';
}

char	*ft_find_line(char *buffer, char *line)
{
	char	*newline_ptr;
	char	*before_newline;
	size_t	len;

	newline_ptr = ft_strrchr(buffer, '\n');
	if (newline_ptr != NULL)
	{
		len = newline_ptr - buffer + 1;
		before_newline = malloc(sizeof(char) * len + 1);
		if (!before_newline)
			return (NULL);
		ft_strlcpy(before_newline, buffer, len + 1);
		before_newline[len] = '\0';
		line = ft_strjoin(line, before_newline);
		if (!line)
			return (free(before_newline), NULL);
		return (free(before_newline), line);
	}
	line = ft_strjoin(line, buffer);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_read_until_newline(char *curr_buffer, int fd)
{
	int		bytecount;
	char	tmp_buffer[BUFFER_SIZE + 1];
	char	*new_buffer;

	while (ft_strrchr(curr_buffer, '\n') == NULL)
	{
		bytecount = read(fd, tmp_buffer, BUFFER_SIZE);
		if (bytecount < 0)
			return (free(curr_buffer), NULL);
		if (bytecount == 0)
		{
			if (curr_buffer[0] != '\0')
				return (curr_buffer);
			return (free(curr_buffer), NULL);
		}
		tmp_buffer[bytecount] = '\0';
		new_buffer = ft_strjoin(curr_buffer, tmp_buffer);
		free(curr_buffer);
		if (!new_buffer)
			return (NULL);
		curr_buffer = new_buffer;
	}
	return (curr_buffer);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*curr_buffer;
	char		*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (buffer[0] = '\0', NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	curr_buffer = ft_strdup(buffer);
	if (!curr_buffer)
		return (free(line), NULL);
	curr_buffer = ft_read_until_newline(curr_buffer, fd);
	if (!curr_buffer)
		return (free(line), NULL);
	next_line = ft_find_line(curr_buffer, line);
	free(line);
	if (!next_line)
		return (free(curr_buffer), NULL);
	return (ft_save_buffer(curr_buffer, buffer), free(curr_buffer), next_line);
}

// int main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	int i = 0;
// 	char *line;
// 	while (i < 7)
// 	{
// 		line = get_next_line(fd);
// 		printf("call %i: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// }
