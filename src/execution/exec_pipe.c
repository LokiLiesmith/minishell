/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:55:38 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/27 10:29:33 by mel              ###   ########.fr       */
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
