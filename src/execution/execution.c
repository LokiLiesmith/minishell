/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:10:26 by mel               #+#    #+#             */
/*   Updated: 2025/12/19 23:40:01 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_fork_check(t_cmd_node *cmd_node, int (*pipe_fd)[2], pid_t *pid,
		char **path)
{
	if (cmd_node->next != NULL)
	{
		if (pipe(*pipe_fd) == -1)
			return (perror("pipe() error"), 1);
	}
	*pid = fork();
	if (*pid < 0)
	{
		fork_error(*pipe_fd, path);
		return (perror("fork() error"), 1);
	}
	if (*path == NULL)
	{
		close(*pipe_fd[0]);
		close(*pipe_fd[1]);
	}
	return (0);
}

static int	execute_cmd(t_cmd_node *cmd_node, pid_t *pid, int *prev_fd,
		t_shell *sh)
{
	int		pipe_fd[2];
	char	*path;
	char	**env_array;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	path = NULL;
	env_array = NULL;
	if (is_builtin(cmd_node->cmd) && cmd_node->next == NULL)
		return (execute_single_builtin(cmd_node->cmd, sh->env, sh));
	if (prepare_execve(cmd_node->cmd, &path, &env_array, sh))
		return (sh->last_exit_code = 127, 127);
	if (pipe_fork_check(cmd_node, &pipe_fd, pid, &path))
		return (1);
	if (*pid == 0)
	{
		if (handle_pipe_child(cmd_node, pipe_fd, *prev_fd))
			exit(1);
		execute_child(path, cmd_node->cmd, env_array);
	}
	else
		close_pipe_parent(*prev_fd, prev_fd, cmd_node, pipe_fd);
	if (path)
		free(path);
	return (0);
}

int	execute_start(t_cmd_node *cmd_node, t_shell *sh)
{
	pid_t		pid;
	t_cmd_node	*curr;
	int			prev_fd;
	int			flag;

	curr = cmd_node;
	prev_fd = -1;
	flag = 0;
	while (curr)
	{
		if (empty_check(curr, sh, &flag) == 1 && curr->next == NULL)
			return (127);
		else if (empty_check(curr, sh, &flag) == 2 && curr->next != NULL)
			curr = curr->next;
		sh->last_exit_code = execute_cmd(curr, &pid, &prev_fd, sh);
		if (sh->last_exit_code)
			return (reset_prev_fd(&prev_fd), sh->last_exit_code);
		curr = curr->next;
	}
	reset_prev_fd(&prev_fd);
	set_parent_wait_signals();
	sh->last_exit_code = wait_for_children(pid);
	signal_setup();
	if_flag(flag);
	return (WEXITSTATUS(sh->last_exit_code));
}
