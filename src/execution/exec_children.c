/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:04:44 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/02 22:09:35 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_child(char *path, t_cmd *cmd, char **env_array)
{
	if (!path)
		exit(127);
	if (!cmd->argv || !env_array || cmd->argv[0][0] == '\0')
		exit(127);
	if (cmd->redirs && handle_redirections(cmd))
    	exit(1);
	if (execve(path, cmd->argv, env_array))
	{
		perror("execve() error");
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
        	exit(126);
    	else
        	exit(1);
	}
}
