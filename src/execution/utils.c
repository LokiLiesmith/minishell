/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:03 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/25 18:53:05 by mel              ###   ########.fr       */
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
	
	// convert env table to a char* array to pass to execve
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

// void	shell_lvl(char **env)
// {
	// update lvl of shell with getenv
// }
