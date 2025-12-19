/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 23:38:48 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/04 00:53:53 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_atty(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

static void	write_to_pipe(char *line, int fd_out)
{
	ft_putstr_fd(line, fd_out);
	ft_putchar_fd('\n', fd_out);
}

int	read_write_to_pipe(t_shell *sh, t_redir *r, int fd_out)
{
	char	*line;
	char	*newline;

	while (1)
	{
		if (is_atty())
			line = readline("heredoc> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			return (1);
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		if (r->delimiter && ft_strcmp(line, r->delimiter) == 0)
		{
			free(line);
			break ;
		}
		line = expand_heredoc(sh, r, line);
		write_to_pipe(line, fd_out);
	}
	return (0);
}
