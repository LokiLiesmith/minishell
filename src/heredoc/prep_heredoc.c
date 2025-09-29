/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:06:46 by mel               #+#    #+#             */
/*   Updated: 2025/09/28 19:51:21 by mel              ###   ########.fr       */
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

static int	read_write_to_pipe(t_shell *sh, t_redir *r, int fd_out)
{
	char	*line;

	while (1)
	{
		if (is_atty())
			line = readline("heredoc> ");
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			return (1);
		if (r->delimiter && ft_strcmp(line, r->delimiter) == 0)
		{
			// printf("[DEBUG] heredoc at delim: %s\n", r->delimiter);
			free(line);
			break ;
		}
		// 	EXPAND STUFF HERE !!
		// printf("[DEBUG] got line!!!: '%s'\n", line);
		line = expand_heredoc(sh, r, line);
		write_to_pipe(line, fd_out);
	}
	return (0);
}

int prepare_heredoc(t_shell *sh, t_cmd_node *pipeline)
{
	t_redir_node	*redir;
	int				pipe_fd[2];
	int				pid;
	
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
				if (read_write_to_pipe(sh, &redir->r, pipe_fd[1]))
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
			redir->r.fd = pipe_fd[0];
		}
		redir = redir->next;
	}
	return (0);
}
