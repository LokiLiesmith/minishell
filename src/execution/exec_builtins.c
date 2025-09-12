/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:04:23 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/13 01:12:10 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../built_ins/built_ins.h"
#include "../built_ins/cd.c"
#include "../built_ins/env.c"
#include "../built_ins/export.c"
#include "../built_ins/pwd.c"
#include "../built_ins/echo.c"
#include "../built_ins/unset.c"



int	is_builtin(t_cmd *cmd)
{
	if (cmd->builtin == NONE)
		return (0);
	return (1);
}

static int	find_builtin(t_cmd *cmd, t_env *env)
{
	if (cmd->builtin == ECHO)
		builtin_echo(cmd);
	else if (cmd->builtin == CD)
		builtin_cd(cmd, env);
	else if (cmd->builtin == PWD)
		builtin_pwd();
	else if (cmd->builtin == ENV)
		builtin_env(cmd, env);
	else if (cmd->builtin == EXPORT)
		builtin_export(cmd, env);
	else if (cmd->builtin == UNSET)
		builtin_unset(cmd, env);
	else if (cmd->builtin == EXIT)
	{
		// builtin_exit(cmd); TODO
		// cleanup	
	}
	else
		ft_putstr_fd("Command not found\n", 2);
	return (0);
}

int execute_single_builtin(t_cmd *cmd, t_env *env)
{
	// save in out
	if (cmd->redirs)
		// save_redirs(cmd);
	find_builtin(cmd, env);
	// reset redirections
	return (0);
}
