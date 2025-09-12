/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:10:26 by mel               #+#    #+#             */
/*   Updated: 2025/09/13 01:11:20 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// #include "../built_ins/built_ins.h"

// - execution single builtin
// - execution single builtin with redirections

// - execution single external
// - execution with pipes
// - execution with redirections

// "HOME" = 4; [0][1][2][3][4]
// HOME=~/abcabc/abc


// EXECUTION_START (exec loop, runs till every command is executed) ->
// EXECUTE_CMD (checks if cmd is builtin, forks the process, FIND_PATH() -> ENV_TO_ARRAY()-> execute)
// 					|									  OR						|
//	-----------------------------------------------------	----------------------------------------------------
//	|						SINGLE BUILTIN				|	|				EXTERNAL CMD						|
//	|			execute_single_builtin(cmd, env)		|	|		execute_child(path, cmd, env_array)			|
//	|							||						|	|													|
//	|		NO REDIR			||		REDIR			|	|													|
//	|  find_builin(cmd, env);	||	handle_fds(TODO)	|	|													|
//	|							||						|	|													|
//	|							||						|	|													|
//	|													|	|													|
//	-----------------------------------------------------	-----------------------------------------------------


char	**env_to_array(t_env *env)
{
	char	**env_array;
	char	*temp;
	t_env	*current;
	int		i;
	size_t	env_len;

	i = 0;
	current = env;
	env_len = 0;
	while (current != NULL)
	{
		current = current->next;
		env_len++;
	}
	env_array = malloc(sizeof(char *) * env_len);
	// convert env table to a char* array to pass to execve
	current = env;
	while (current != NULL)
	{
		temp = ft_strjoin(env->type, "=");
		env_array[i] = ft_strjoin(temp, env->value);
		free(temp);
		i++;
		current = current->next;
	}
	env_array[i][0] = '\0';
	return (env_array);
}

// TODO
void	handle_fds(t_cmd *cmd)
{
	int				in;
	int				out;
	t_redir_node	*redir_node;
	
	// CHECK RETURN OF OPEN()
	redir_node = cmd->redirs;
	if (redir_node->r.type == R_IN)
	{
		in = open("", O_RDONLY);
		dup2(in, STDIN_FILENO);
		// save in
	}
	if (redir_node->r.type == R_OUT)
	{
		out = open("", O_WRONLY | O_CREAT, 0777);
		dup2(out, STDOUT_FILENO);
		// save out
	}
	
}

// return on error
static int	execute_cmd(t_cmd_node *node, t_cmd *cmd, t_env *env, pid_t *pid)
{
	char	*path;
	char	**env_array;
	int		status;
	pid_t	wpid;

	// are there redirections ? save fds
	*pid = fork();
	path = find_path(cmd, env);
	if (!path)
	{
		ft_putstr_fd("Command not found", 2);
		return (1); // return value idk
	}
	if (is_builtin(cmd) && node->next == NULL)
		execute_single_builtin(cmd, env);
	env_array = env_to_array(env);
	if (pid == 0) // return 0 = child process
	{
		// if (cmd->redirs)
			// handle_fds(cmd);
		// set up pipes here
		execute_child(path, cmd, env_array); // check return value
	}
	else if (pid > 0) // parent process
	{
		wpid = waitpid(*pid, &status, 0); // wait for the child process
		if (wpid == -1)
		{
			perror("waitpid() error");
			return (1);
		}
	}
	else
	{
		perror("fork() error");
		return (1);
	}
	return (0);
}

int	execute_start(t_cmd_node *node, t_env *env)
{
	pid_t		pid;
	t_cmd_node	*cmd;

	cmd = node;
	// check if theres more than one cmd
	// check if builtin
	// check if builtin with redirections
	// fork, child process calls execve, parent wait for the child to finish
	{
		while (cmd)
		{
			if (execute_cmd(node, cmd->cmd, env, &pid))
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
