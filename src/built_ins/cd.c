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

// int	update_pwd(t_env *env)
// {
// 	t_env	*current;
// 	char	*current_dir;
	
// 	current = env;
// 	current_dir = getcwd(NULL, 0);
// 	// error check
// 	while (ft_strncmp(current->type, "PWD", 3) && current != NULL)
// 		current = current->next;
// 	current->value = current_dir;
// 	return (0);
// }

// int	update_oldpwd(t_env *env, char *old_dir)
// {
// 	t_env	*current;

// 	current = env;
// 	while (ft_strncmp(current->type, "OLDPWD", 6) && current != NULL)
// 		current = current->next;
// 	current->value = old_dir;
// 	return (0);
// }

// int	builtin_cd(t_cmd *cmd, t_env *env)
// {
// 	char	*old_dir;
// 	char	*current_dir;
	
// 	old_dir = getcwd(NULL, 0);
// 	current_dir = cmd->argv[1]; // argv[0] = "cd"
// 	// TILDA HANDLING AAAAAAAAAAA
// 	if (chdir(current_dir) != 0)
// 	{
// 		perror("chdir() failed");
// 		return (1);
// 	}
// 	update_pwd(env);
// 	update_oldpwd(env, old_dir);
// 	return (0);
// }


///GPT PROPOSED CHANGES
void set_env_value(t_shell *sh, t_env *env, const char *key, const char *new_value)
{
    t_env *current = env;

    while (current)
    {
        if (ft_strcmp(current->type, (char *)key) == 0)
        {
            current->value = gc_strdup(sh, new_value, GC_GLOBAL);
            return;
        }
        if (!current->next) // reached end
            break;
        current = current->next;
    }

    // Create new node if not found
    t_env *new_node = gc_malloc(sh, sizeof(t_env), GC_GLOBAL);
    if (!new_node)
        return;
    new_node->type = gc_strdup(sh, key, GC_GLOBAL);
    new_node->value = gc_strdup(sh, new_value, GC_GLOBAL);
    new_node->next = NULL;

    if (current)
        current->next = new_node;
    else
        env = new_node; // in case env list was empty
}

static char *get_env_raw(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_strcmp(env->type, (char *)key) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

static void cd_error(const char *arg)
{
    ft_putstr_fd("minishell: cd: ", 2);
    if (arg)
    {
        ft_putstr_fd((char *)arg, 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putendl_fd((char *)strerror(errno), 2);
}
int builtin_cd(t_cmd *cmd, t_env *env, t_shell *sh)
{
    char *target;
    char *old_dir;
    char *new_dir;

    old_dir = getcwd(NULL, 0);

    if (!cmd->argv[1]) // case: cd
    {
        target = get_env_raw(env, "HOME");
        if (!target)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            free(old_dir);
            return 1;
        }
    }
    else if (ft_strcmp(cmd->argv[1], "-") == 0) // case: cd -
    {
        target = get_env_raw(env, "OLDPWD");
        if (!target)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            free(old_dir);
            return 1;
        }
        if (chdir(target) != 0)
        {
            cd_error(target);
            free(old_dir);
            return 1;
        }
        ft_putendl_fd(target, 1); // print new dir
        new_dir = getcwd(NULL, 0);
        set_env_value(sh, env, "OLDPWD", old_dir);
        set_env_value(sh, env, "PWD", new_dir);
        free(old_dir);
        free(new_dir);
        return 0;
    }
    else // case: cd <path>
    {
        target = cmd->argv[1];
    }

    if (chdir(target) != 0)
    {
        cd_error(target);
        free(old_dir);
        return 1;
    }

    new_dir = getcwd(NULL, 0);
    set_env_value(sh, env, "OLDPWD", old_dir);
    set_env_value(sh, env, "PWD", new_dir);
    free(old_dir);
    free(new_dir);
    return 0;
}