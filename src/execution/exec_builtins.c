/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:04:23 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/29 16:41:25 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (cmd->builtin == NONE)
		return (0);
	return (1);
}

int	find_builtin(t_cmd *cmd, t_env *env, t_shell *sh)
{
	if (cmd->builtin == ECHO)
		return (builtin_echo(cmd));
	else if (cmd->builtin == CD)
		return (builtin_cd(cmd, env));
	else if (cmd->builtin == PWD)
		return (builtin_pwd());
	else if (cmd->builtin == ENV)
		return (builtin_env(cmd, env));
	else if (cmd->builtin == EXPORT)
		return (builtin_export(cmd, env, sh));
	else if (cmd->builtin == UNSET)
		return (builtin_unset(cmd, env));
	else if (cmd->builtin == EXIT)
		builtin_exit(sh, cmd);
	ft_putstr_fd("command not found\n", 2);
	return (1);
}
// void save_fds(int saved_stdin, int saved_stdout)
// {
//     saved_stdin = dup(STDIN_FILENO);
//     saved_stdout = dup(STDOUT_FILENO);

//     if (saved_stdin < 0 || saved_stdout < 0)
//         perror("dup() error in save_fds");
// }

int execute_single_builtin(t_cmd *cmd, t_env *env, t_shell *sh)
{
	static int	saved_stdin;
	static int	saved_stdout;
	int			ret;

	ret = 1;
	saved_stdin = -1;
	saved_stdout = -1;
	if (cmd->redirs != NULL)
	{
		saved_stdin = dup(STDIN_FILENO);
    	saved_stdout = dup(STDOUT_FILENO);

   		if (saved_stdin < 0 || saved_stdout < 0)
        	perror("dup() error in save_fds");
		if (handle_redirections(cmd))
		{
			// restore_fds();
			return (1);
		}
	}
	ret = find_builtin(cmd, env, sh);
	if (cmd->redirs != NULL)
	{
    	if (saved_stdin >= 0)
    	{
    	    dup2(saved_stdin, STDIN_FILENO); // restore stdin
       		close(saved_stdin);              // close copy
        	saved_stdin = -1;
    	}
	    if (saved_stdout >= 0)
    	{
        	dup2(saved_stdout, STDOUT_FILENO); // restore stdout
        	close(saved_stdout);               // close copy
        	saved_stdout = -1;
 	   	}
	}
	return (ret);
}
