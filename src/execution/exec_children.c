/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:04:44 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/12 19:14:17 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_child(char *path, t_cmd *cmd, char **env_array)
{
	if (execve(path, cmd->argv, env_array))
	{
		perror("execve() error");
		exit(EXIT_FAILURE); // return 127?
	}
}
