/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:06:46 by mel               #+#    #+#             */
/*   Updated: 2025/10/04 04:38:08 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_heredoc_child(t_shell *sh, t_redir *redir, int *pipe_fd)
{
	set_child_signals();
	close(pipe_fd[0]);
	if (read_write_to_pipe(sh, redir, pipe_fd[1]))
	{
		close(pipe_fd[1]);
		exit(1);
	}
	close(pipe_fd[1]);
	exit(0);
}

static int	handle_heredoc_parent(t_shell *sh, int pid, int *pipe_fd)
{
	int	status;

	set_parent_wait_signals();
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	signal_setup();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		sh->last_exit_code = 130;
		close(pipe_fd[0]);
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		fprintf(stderr, "warning: heredoc delimited by EOF\n");
		close(pipe_fd[0]);
		return (1);
	}
	return (0);
}

static int	pipe_setup(int (*pipe_fd)[2], int *pid)
{
	if (pipe(*pipe_fd) == -1)
		return (perror("pipe"), 1);
	*pid = fork();
	if (*pid < 0)
		return (error_pid(*pipe_fd), perror("fork"), 1);
	return (0);
}

static int	process_hdoc(t_shell *sh, t_redir_node *r)
{
	int				pipe_fd[2];
	int				pid;

	if (pipe_setup(&pipe_fd, &pid))
		return (1);
	if (pid == 0)
		handle_heredoc_child(sh, &r->r, pipe_fd);
	else if (handle_heredoc_parent(sh, pid, pipe_fd))
		return (1);
	r->r.type = R_IN;
	r->r.fd = pipe_fd[0];
	return (0);
}

int	prepare_heredoc(t_shell *sh, t_cmd_node *pipeline)
{
	t_redir_node	*redir;
	t_cmd_node		*curr;

	curr = pipeline;
	while (curr != NULL)
	{
		redir = curr->cmd->redirs;
		while (redir)
		{
			if (redir->r.type == R_HEREDOC)
			{
				if (process_hdoc(sh, redir))
					return (1);
			}
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (0);
}
