/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:03 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/02 18:02:17 by msalangi         ###   ########.fr       */
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

// int	put_env(t_env *env, char ***env_array)
// {
// 	t_env	*current;
// 	int		i;
// 	char	*temp;
// 	char	*temp2;
	
// 	i = 0;
// 	current = env;
// 	while (current != NULL)
// 	{
// 		temp = ft_strjoin(current->type, "=");
// 		if (!temp)
// 			return (1);
// 		temp2 = ft_strjoin(temp, current->value);
// 		if (!temp2)
// 			return (1);
// 		*env_array[i] = temp2;
// 		free(temp);
// 		free(temp2);
// 		i++;
// 		current = current->next;
// 	}
// 	return (0);
// }


char	**env_to_array(t_env *env, t_shell *sh)
{
	char	**env_array;
	char	*temp;
	char	*temp2;
	t_env	*current;
	size_t	env_len;

	current = env;
	env_len = 0;
	int i = 0;
	while (current != NULL)
	{
		current = current->next;
		env_len++;
	}
	env_array = gc_malloc(sh, sizeof(char *) * (env_len + 1), GC_GLOBAL);
	if (!env_array)
		return (NULL);
	env_array[env_len] = NULL;
	
	// if (put_env(env, &env_array))
	// 	return (NULL);
	current = env;
	while (current != NULL)
	{
		temp = ft_strjoin(current->type, "=");
		temp2 = ft_strjoin(temp, current->value);
		env_array[i] = temp2;
		free(temp);
		free(temp2);
		i++;
		current = current->next;
	}
	return (env_array);
}

int	prepare_execve(t_cmd *cmd, t_env *env, char **path, char ***env_array, t_shell *sh)
{
	*path = find_path(cmd, env);
	if (!*path)
	{
		ft_putstr_fd("command not found\n", 2);
		sh->last_exit_code = 127;
		return (127);
	}
	*env_array = env_to_array(env, sh);
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
