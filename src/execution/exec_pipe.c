/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:55:38 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/25 21:04:14 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_pipe_child(t_cmd_node *cmd, int pipe_fd[], int prev_fd)
{
	if (prev_fd != -1) // if not first
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
			perror("dup2() error");
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			perror("dup2() error");
        close(pipe_fd[1]);
	}
	if (cmd->next == NULL)
	{
		// close unused fds
	}
	return (0);
}

// ls | wc -l

// ls | grep s
// ls is stdin of pipe, pipe is stdout of ls; pipe is stdin of grep