/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:10:26 by mel               #+#    #+#             */
/*   Updated: 2025/09/15 03:45:57 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// #include "../built_ins/built_ins.h"

// - execution single builtin +
// - execution single builtin with redirections -

// - execution single external +
// - execution with pipes -
// - execution with redirections -


// EXECUTION_START (exec loop, runs till every command is executed) ->
// EXECUTE_CMD (checks if cmd is builtin, forks the process, FIND_PATH() -> ENV_TO_ARRAY()-> execute)
// 					|									  OR						|
//	-----------------------------------------------------	----------------------------------------------------
//	|						SINGLE BUILTIN				|	|				EXTERNAL CMD						|
//	|			execute_single_builtin(cmd, env)		|	|		execute_child(path, cmd, env_array)			|
//	|							||						|	|		redirect()									|
//	|		NO REDIR			||		REDIR			|	|		handle_pipes()								|
//	|  find_builin(cmd, env);	||	redirect(TODO)		|	|													|
//	|							||						|	|													|
//	|							||						|	|													|
//	|													|	|													|
//	-----------------------------------------------------	-----------------------------------------------------



// ls | grep s	> test.txt	= "src" in test.txt
// ls -> ... into pipe (pipe should be stdout for that child process)
// pipe -> grep s -> stdout (after returning to the parent process, we restore stdout)



// return on error
static int	execute_cmd(t_cmd_node *node, t_cmd *cmd, t_env *env, pid_t *pid)
{
	int		pipe_fd[2];		// fd[0] - read; fd[1] - write
	char	*path;
	char	**env_array;
	int		status;
	pid_t	wpid;

	// are there redirections ?
	if (cmd->redirs)
		redirect(cmd);

	// SINGLE BUILTIN - NO PIPES. HANDLE REDIRECTIONS
	if (is_builtin(cmd) && node->next == NULL)
		execute_single_builtin(cmd, env);

	path = find_path(cmd, env);
	if (!path)
		return (ft_putstr_fd("Command not found", 2), 1);
	env_array = env_to_array(env);
	if (!env)
		return (ft_putstr_fd("env_array() error", 2), 1);

	// PIPE before fork
	if (pipe(pipe_fd) == -1)
		return (perror("pipe() error"), 1);
	// if (node->next)
		// handle_pipe();

	*pid = fork(); // fork returns twice; when fork, fds copy over
	if (*pid < 0)
		return (perror("fork() error"), 1);
	else if (*pid == 0) // return 0 = child process
	{
		execute_child(path, cmd, env_array); // check return value
	}
	else if (*pid > 0) // parent process
	{
		wpid = waitpid(*pid, &status, 0); // wait for the child process
		if (wpid == -1)
			return (perror("waitpid() error"), 1);
	}
	return (0);
}

int	execute_start(t_cmd_node *node, t_env *env)
{
	pid_t		pid;
	t_cmd_node	*cmd;

	cmd = node;
	// chek pid for return values ?
	while (cmd)
	{
		if (execute_cmd(node, cmd->cmd, env, &pid))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
