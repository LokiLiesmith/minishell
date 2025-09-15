/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:54:03 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/15 00:54:06 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

// void	shell_lvl(char **env)
// {
	// update lvl of shell with getenv
// }
