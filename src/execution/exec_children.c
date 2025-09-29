/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:04:44 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/28 22:21:49 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_child(char *path, t_cmd *cmd, char **env_array)
{
	if (!path || !cmd->argv || !env_array)
		exit(1);
	if (cmd->redirs && handle_redirections(cmd))
    	exit(1);
	if (execve(path, cmd->argv, env_array))
	{
		perror("execve() error");
		exit(EXIT_FAILURE); // return 127?
	}
}
