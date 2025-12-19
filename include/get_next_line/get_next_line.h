/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 01:20:00 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/04 02:15:04 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_read_until_newline(char *curr_buffer, int fd);
char	*ft_find_line(char *buffer, char *line);
void	ft_save_buffer(char *curr_buffer, char *buffer);

// size_t	ft_strlen(const char *s);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// char	*ft_strrchr(const char *s, int c);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_strdup(char *s1);

#endif
