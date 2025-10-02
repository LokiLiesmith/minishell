/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 23:46:42 by mel               #+#    #+#             */
/*   Updated: 2025/10/02 20:50:54 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_pwd(t_env *env)
{
	t_env	*current;
	char	*current_dir;
	
	current = env;
	current_dir = getcwd(NULL, 0);
	// error check
	while (ft_strncmp(current->type, "PWD", 3) && current != NULL)
		current = current->next;
	current->value = current_dir;
	return (0);
}

int	update_oldpwd(t_env *env, char *old_dir)
{
	t_env	*current;

	current = env;
	while (ft_strncmp(current->type, "OLDPWD", 6) && current != NULL)
		current = current->next;
	current->value = old_dir;
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_env *env)
{
	char	*old_dir;
	char	*current_dir;
	
	old_dir = getcwd(NULL, 0);
	current_dir = cmd->argv[1]; // argv[0] = "cd"
	// TILDA HANDLING AAAAAAAAAAA
	if (chdir(current_dir) != 0)
	{
		perror("chdir() failed");
		return (1);
	}
	update_pwd(env);
	update_oldpwd(env, old_dir);
	return (0);
}
