/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:06:46 by mel               #+#    #+#             */
/*   Updated: 2025/09/28 18:43:08 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_atty(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

static void	write_to_pipe(char *line, int fd_out)
{
	ft_putstr_fd(line, fd_out);
	ft_putchar_fd('\n', fd_out);
}

static int	read_write_to_pipe(char *delimiter, int fd_out)
{
	char	*line;

	while (1)
	{
		if (is_atty())
			line = readline("> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			return (1);
		if (delimiter && ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		// 	EXPAND STUFF HERE !!
		write_to_pipe(line, fd_out);
	}
	return (0);
}

int prepare_heredoc(t_cmd_node *pipeline, t_shell *sh)
{
	t_redir_node	*redir;
	int				pipe_fd[2];
	int				pid;
	int				fd_len;
	char			*store_fd;
	
	redir = pipeline->cmd->redirs;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	while (redir != NULL)
	{
		if (redir->r.type == R_HEREDOC)
		{
			if (pipe(pipe_fd) == -1)
				return (1);
			pid = fork();
			if (pid < 0)
				return (error_pid(pipe_fd), perror("fork() error"), 1);
			else if (pid == 0) // child
			{
				if (read_write_to_pipe(redir->r.delimiter, pipe_fd[1]))
					return (close(pipe_fd[0]), exit(1), 1);
				close(pipe_fd[0]);
				exit(0);
			}
			else // parent
			{
				close(pipe_fd[1]);
				waitpid(pid, NULL, 0);
			}
			redir->r.type = R_IN;
			store_fd = ft_itoa(pipe_fd[0]);
			fd_len = ft_strlen(store_fd);
			redir->r.target = gc_malloc(sh, fd_len + 1, GC_TEMP);
			redir->r.target[fd_len] = '\0';
			ft_strlcpy(redir->r.target, store_fd, fd_len);
		}
		redir = redir->next;
	}
	return (0);
}
