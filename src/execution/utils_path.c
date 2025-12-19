/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:29:25 by msalangi          #+#    #+#             */
/*   Updated: 2025/12/19 23:40:08 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*search_directories(char **directories, char *command)
{
	char	*full_path;
	char	*part_path;
	int		i;

	i = 0;
	while (directories[i] != NULL)
	{
		part_path = ft_strjoin(directories[i], "/");
		if (!part_path)
			return (NULL);
		full_path = ft_strjoin(part_path, command);
		free(part_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*find_path(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**directories;
	t_env	*current;
	char	*command;

	path = NULL;
	command = cmd->argv[0];
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	current = env;
	while (current && ft_strncmp(current->type, "PATH", 4) != 0)
		current = current->next;
	if (!current || !current->value || current->value[0] == '\0')
		directories = ft_split("/bin:/usr/bin", ':');
	else
		directories = ft_split(current->value, ':');
	if (!directories)
		return (NULL);
	path = search_directories(directories, command);
	free_split(directories);
	return (path);
}
