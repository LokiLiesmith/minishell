/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:10:26 by mel               #+#    #+#             */
/*   Updated: 2025/09/25 18:58:53 by mel              ###   ########.fr       */
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
static int	execute_cmd(t_cmd_node *cmd_node, t_env *env, pid_t *pid)
{
	int			pipe_fd[2];		// fd[0] - read; fd[1] - write
	static int	prev_fd = -1;	
	char		*path;
	char		**env_array;

	// SINGLE BUILTIN - NO PIPES. HANDLE REDIRECTIONS
	// if (is_builtin(cmd->cmd) && cmd->next == NULL)
		// return (execute_single_builtin(cmd->cmd, env));

	path = find_path(cmd_node->cmd, env);
	if (!path)
		return (ft_putstr_fd("Command not found", 2), 1);
	env_array = env_to_array(env);
	if (!env_array)
		return (ft_putstr_fd("env_array() error", 2), 1);

	// PIPE before fork
	if (cmd_node->next && pipe(pipe_fd) == -1)
		return (perror("pipe() error"), 1);

	*pid = fork(); // fork returns twice; when fork, fds copy over
	if (*pid < 0)
		return (perror("fork() error"), 1);
	else if (*pid == 0) // return 0 = child process
	{
		if (cmd_node->next)
			handle_pipe_child(cmd_node, pipe_fd, prev_fd);
		execute_child(path, cmd_node->cmd, env_array);
	}
	else
	{
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd_node->next)
		{
			close(pipe_fd[1]);		// close write end in parent
			prev_fd = pipe_fd[0];	// save read end for next cmd
		}
	}
	return (0);
}

int	execute_start(t_cmd_node *cmd_node, t_env *env)
{
	pid_t		pid;
	int 		last_status;
	t_cmd_node	*curr;

	curr = cmd_node;
	while (curr)
	{
		if (execute_cmd(curr, env, &pid))
			return (1);
		curr = curr->next;
	}
	last_status = wait_for_children(pid);
	return (WEXITSTATUS(last_status)); // returns exit code of the last command
}
