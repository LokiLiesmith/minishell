/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:03 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/27 19:46:56 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_for_children(pid_t last_child)
{
	int wpid;
	int	status;
	int	last_status;

	status = 0;
	last_status = 0;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid <= 0)
			break ;
		if (wpid == last_child)
			last_status = status;
	}
	return (last_status);
}

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
	env_array = malloc(sizeof(char *) * (env_len + 1));
	if (!env_array)
		return (NULL);
	env_array[env_len] = NULL;
	
	current = env;
	while (current != NULL)
	{
		temp = ft_strjoin(current->type, "=");
		env_array[i] = ft_strjoin(temp, current->value);
		free(temp);
		i++;
		current = current->next;
	}
	return (env_array);
}

int	prepare_execve(t_cmd *cmd, t_env *env, char **path, char ***env_array) //cmd_node->cmd, env, &path, &env_array)
{
	*path = find_path(cmd, env);
	if (!*path)
		return (ft_putstr_fd("Command not found\n", 2), 1);
	*env_array = env_to_array(env);
	if (!*env_array)
		return (ft_putstr_fd("env_array() error", 2), 1);
	return (0);
}

void	error_pid(int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
    if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}
