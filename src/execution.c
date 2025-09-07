/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:10:26 by mel               #+#    #+#             */
/*   Updated: 2025/09/07 20:01:01 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_cmd cmd)
{
	if (cmd.builtin == NONE)
		return (0);
	return (1);
}

int	find_builtin(t_cmd *cmd, t_env *env)
{
if (cmd->builtin == ECHO)
		builtin_echo(cmd);
	else if (cmd->builtin == CD)
		builtin_cd(cmd, env);
	else if (cmd->builtin == PWD)
		builtin_pwd(cmd, env);
	else if (cmd->builtin == ENV)
		builtin_env(cmd, env);
	else if (cmd->builtin == EXPORT)
		builtin_export(cmd, env);
	else if (cmd->builtin == UNSET)
		builtin_unset(cmd, env);
	else if (cmd->builtin == EXIT)
	{
		builtin_exit(cmd);
		// cleanup	
	}
	else
		ft_putstr_fd("Command not found\n", 2);
}

int execute_single_builtin(t_cmd *cmd, t_env *env)
{
	find_builin(cmd, env);
}

void	execute(t_cmd_node *node, t_env *env)
{
	pid_t	pid;

	// are there redirections ? save fds
	// check if theres more than one cmd
	// check if builtin
	if (is_builtin(node->cmd) && node->next == NULL)
		execute_single_builtin(&node->cmd, env);

	// else
	// fork, child process calls execve
}
