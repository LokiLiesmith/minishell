/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:30:16 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/04 06:21:35 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	if_flag(int flag)
{
	if (flag)
		ft_putstr_fd(" : command not found\n", 2);
}

void	fork_error(int pipe_fd[2], char **path)
{
	error_pid(pipe_fd);
	if (*path)
		free(path);
}

void	reset_prev_fd(int *prev_fd)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
}

int	empty_check(t_cmd_node *curr, t_shell *sh, int *flag)
{
	if ((!curr->cmd->argv[0] || curr->cmd->argv[0][0] == '\0') && !curr->next)
	{
		ft_putstr_fd(" : command not found\n", 2);
		sh->last_exit_code = 127;
		return (1);
	}
	if (ft_strcmp(curr->cmd->argv[0], "") == 0 || ft_strcmp(curr->cmd->argv[0],
			" ") == 0)
	{
		if (curr->next != NULL)
		{
			*flag = 1;
			return (2);
		}
		else
		{
			ft_putstr_fd(" : command not found\n", 2);
			sh->last_exit_code = 127;
			return (1);
		}
	}
	return (0);
}
