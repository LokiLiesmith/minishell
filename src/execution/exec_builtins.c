/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:04:23 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/03 22:32:10 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (cmd->builtin == NONE)
		return (0);
	return (1);
}

static int	find_builtin(t_cmd *cmd, t_env *env, t_shell *sh)
{
	if (cmd->builtin == ECHO)
		return (builtin_echo(cmd));
	else if (cmd->builtin == CD)
		return (builtin_cd(cmd, env, sh));
	else if (cmd->builtin == PWD)
		return (builtin_pwd());
	else if (cmd->builtin == ENV)
		return (builtin_env(cmd, env));
	else if (cmd->builtin == EXPORT)
		return (builtin_export(cmd, env, sh));
	else if (cmd->builtin == UNSET)
		return (builtin_unset(cmd, &sh->env));
	else if (cmd->builtin == EXIT)
		return (builtin_exit(sh, cmd));
	else
		ft_putstr_fd("command not found\n", 2);
	sh->last_exit_code = 127;
	return (1);
}

static int	save_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin < 0 || *saved_stdout < 0)
	{
		perror("dup() error in save_fds");
		return (1);
	}
	return (0);
}

static int	restore_fds(int *saved_stdin, int *saved_stdout)
{
	if (*saved_stdin >= 0)
	{
		dup2(*saved_stdin, STDIN_FILENO);
		close(*saved_stdin);
		*saved_stdin = -1;
	}
	if (*saved_stdout >= 0)
	{
		dup2(*saved_stdout, STDOUT_FILENO);
		close(*saved_stdout);
		*saved_stdout = -1;
	}
	return (0);
}

int	execute_single_builtin(t_cmd *cmd, t_env *env, t_shell *sh)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	ret = 1;
	saved_stdin = -1;
	saved_stdout = -1;
	if (cmd->redirs != NULL)
	{
		if (save_fds(&saved_stdin, &saved_stdout))
			return (1);
		if (handle_redirections(cmd))
		{
			restore_fds(&saved_stdin, &saved_stdout);
			return (1);
		}
	}
	ret = find_builtin(cmd, env, sh);
	if (cmd->redirs != NULL)
		restore_fds(&saved_stdin, &saved_stdout);
	return (ret);
}
