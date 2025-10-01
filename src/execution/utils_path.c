/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:29:25 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/01 03:02:09 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*search_directories(char **directories, char *command)
{
	char	*full_path;
	char	*part_path;
	char 	*temp;
	int		i;

	i = 0;
	while (directories[i] != NULL)
	{
		part_path = ft_strjoin(directories[i], "/");
		temp = ft_strjoin(part_path, command);
		full_path = temp;
		free(part_path);
		// free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

void    free_split(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char	*find_path(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**directories;
	t_env	*current;
	char	*command;

	path = NULL;
	current = env;
	command = cmd->argv[0];
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	while (current && ft_strncmp(current->type, "PATH", 4) != 0)
		current = current->next;
	if (!current || !current->value || current->value[0] == '\0')
	{
    	directories = ft_split("/bin:/usr/bin", ':');
    	if (!directories)
        	return (NULL);
    	path = search_directories(directories, command);
    	free_split(directories);
	    return path;
	}
	else if (ft_strncmp(current->type, "PATH", 4) == 0)
	{
		directories = ft_split(current->value, ':');
		if (!directories)
			return (NULL);
		path = search_directories(directories, command);
		free_split(directories);
	}
	// path = search_directories(directories, command);
    // free_split(directories);
	return (path);
}
