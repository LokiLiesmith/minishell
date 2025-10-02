/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:55:38 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/02 17:45:30 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipe_child(t_cmd_node *cmd, int pipe_fd[], int prev_fd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
			return (perror("dup2() error"), 1);
		close(prev_fd);
	}
	if (cmd->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			return (perror("dup2() error"), 1);
        close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (0);
}

void	close_pipe_parent(int prev_fd, int *prev_fd_ptr, t_cmd_node *cmd_node, int pipe_fd[2])
{	
	if (prev_fd != -1)
	{
		close(prev_fd);
		*prev_fd_ptr = -1;
	}
	if (cmd_node->next)
	{
		close(pipe_fd[1]);
		*prev_fd_ptr = pipe_fd[0];
	}
	else
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
		*prev_fd_ptr = -1;
	}
}
