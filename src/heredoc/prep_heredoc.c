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

int prepare_heredoc(t_shell *sh, t_cmd_node *pipeline) //think we can go void and not int, the signals will set the error code
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
			if (pid < 0) //do we need to close pipes in this case?
				return (error_pid(pipe_fd), perror("fork() error"), 1);
			else if (pid == 0) // child
			{
				set_child_signals();
				if (read_write_to_pipe(sh, &redir->r, pipe_fd[1]))
				{
					close(pipe_fd[0])
					exit (1);
				}
					return (close(pipe_fd[0]), exit(1), 1); // return or just exit?
				close(pipe_fd[0]);
				exit(0);
			}
			else // parent
			{
				set_parent_wait_signals();
				close(pipe_fd[1]);
				waitpid(pid, NULL, 0);
				signal_setup(); //revert signal handling to regular shell
				
				//TODO
				// we need to check how child died to set the correct error code
				// rn it dumps everything inside pipe with both exits
				// if ctrl + c shouldnt print anything
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
                {
                    sh->last_exit_code = 130;
                    close(pipe_fd[0]);
                    return (1); // abort pipeline
                }
				if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
                {
                    // Ctrl-D case → continue, but optional warning
                    fprintf(stderr, "minishell: warning: heredoc delimited by EOF\n");
                }
			}
			redir->r.type = R_IN;
			redir->r.fd = pipe_fd[0];
		}
		redir = redir->next;
	}
	return (0);
}
