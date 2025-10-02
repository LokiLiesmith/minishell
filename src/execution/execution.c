/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:10:26 by mel               #+#    #+#             */
/*   Updated: 2025/10/02 17:46:10 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// #include "../built_ins/built_ins.h"

// - execution single builtin 
// - execution single builtin with redirections -

// - execution single external 
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

static int	execute_cmd(t_cmd_node *cmd_node, t_env *env, pid_t *pid, int *prev_fd_ptr, t_shell *sh)
{
	int			pipe_fd[2];
	char		*path;
	char		**env_array;
	int			prev_fd = *prev_fd_ptr;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (is_builtin(cmd_node->cmd) && cmd_node->next == NULL)
		return (execute_single_builtin(cmd_node->cmd, env, sh));
	if (prepare_execve(cmd_node->cmd, env, &path, &env_array, sh))
		return (sh->last_exit_code = 127, 127);
	if (cmd_node->next != NULL)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe() error"), 1);
	}
	*pid = fork();
	if (*pid < 0)
		return (error_pid(pipe_fd), perror("fork() error"), 1);
	else if (*pid == 0)
	{
		if (handle_pipe_child(cmd_node, pipe_fd, prev_fd))
			exit(1);
		execute_child(path, cmd_node->cmd, env_array);
	}
	else
		close_pipe_parent(prev_fd, prev_fd_ptr, cmd_node, pipe_fd);
	return (0);
}

int	execute_start(t_cmd_node *cmd_node, t_shell *sh)
{
	t_env		*env;
	pid_t		pid;
	int 		last_status;
	t_cmd_node	*curr;
	int			prev_fd;
	int			flag;

	env = sh->env;
	curr = cmd_node;
	prev_fd = -1;
	flag = 0;
	while (curr)
	{
		if (!curr->cmd->argv[0] || curr->cmd->argv[0][0] == '\0')
		{
    		ft_putstr_fd(" : command not found\n", 2);
    		sh->last_exit_code = 127;
    		return (127);
		}
		if (ft_strcmp(curr->cmd->argv[0], "") == 0)
		{
			flag = 1;
			if (curr->next != NULL)
				curr = curr->next;
			else
			{
				ft_putstr_fd(" : command not found\n", 2);
				sh->last_exit_code = 127;
				return (127);
			}
		}
		if (execute_cmd(curr, env, &pid, &prev_fd, sh))
			return (1);
		curr = curr->next;
	}
	if (prev_fd != -1)
	{
		close(prev_fd);
		prev_fd = -1;		
	}
	last_status = wait_for_children(pid);
	if (flag)
	{
		ft_putstr_fd(" : command not found\n", 2);
	}
	return (WEXITSTATUS(last_status));
}
