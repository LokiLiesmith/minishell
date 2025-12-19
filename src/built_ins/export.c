/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 01:17:33 by mel               #+#    #+#             */
/*   Updated: 2025/12/19 23:38:33 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// // /ORIGINAL

// static	int change_export_value(t_shell *sh, t_env *current, char *value)
// {
// 	current->value = gc_malloc(sh, ft_strlen(value) + 1, GC_GLOBAL);
// 	if (!current->value)
// 		return (1);
// 	ft_strlcpy(current->value, value, ft_strlen(value) + 1);
// 	return (0);
// }

// static int	export_allocate(t_shell *sh, t_env *current, t_env *temp,
		//char *type, char *value)
// {
// 	current->next = gc_malloc(sh, sizeof(t_env), GC_GLOBAL);
// 	if (!current->next)
// 		return (1);
// 	current->next->type = gc_malloc(sh, ft_strlen(type) + 1, GC_GLOBAL);
// 	current->next->value = gc_malloc(sh, ft_strlen(value) + 1, GC_GLOBAL);
// 	if (!current->next->value || !current->next->type)
// 		return (1);
// 	ft_strlcpy(current->next->type, type, ft_strlen(type) + 1);
// 	ft_strlcpy(current->next->value, value, ft_strlen(value) + 1);
// 	current->next->next = temp;
// 	return (0);
// }

// int	builtin_export(t_cmd *cmd, t_env *env, t_shell *sh)
// {
// 	t_env	*current;
// 	t_env	*temp;
// 	char	*value;
// 	char	*type;

// 	current = env;
// 	if (current->next && current->type[0] == '_')
// 		current = current->next;
// 	if (cmd->argv[1] == NULL)
// 		export_print(env);
// 	else
// 	{
// 		if (cmd->argv[1][0] == '=' || cmd->argv[1][0] == '\0')
// 			return (ft_putstr_fd("not a valid identifier\n", 2), 1);
// 		value = ft_strrchr(cmd->argv[1], '=');
// 		if (!value)
// 			return (ft_putstr_fd("invalid input\n", 2), 1);
// 		value = value + 1;
// 		*(value - 1)= '\0';
// 		type = cmd->argv[1];
// 		while (current->next != NULL && ft_strcmp(current->type, type) != 0)
// 			current = current->next;
// 		if (ft_strcmp(current->type, type) == 0)
// 			return (change_export_value(sh, current, value));
// 		temp = current->next;
// 		if (export_allocate(sh, current, temp, type, value))
// 			return (1);
// 	}
// 	return (0);
// }

#include "../../include/minishell.h"

static int	is_valid_identifier(char *s)
{
	int	i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	export_print(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->type, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

void	print_invalid(t_cmd *cmd, int i, char **equal, char **type)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd->argv[i], 2);
	ft_putendl_fd("': not a valid identifier", 2);
	if (*equal)
		free(*type);
}

void	set_type_value(char **type, char **value, char *t_val, char *v_val)
{
	*type = t_val;
	*value = v_val;
}

int	builtin_export(t_cmd *cmd, t_env *env, t_shell *sh)
{
	char	*equal;
	char	*type;
	char	*value;
	int		i;

	i = 1;
	if (!cmd->argv[1])
		return (export_print(env), 0);
	while (cmd->argv[i])
	{
		equal = ft_strchr(cmd->argv[i], '=');
		if (equal)
			set_type_value(&type, &value, ft_substr(cmd->argv[i], 0, equal
					- cmd->argv[i]), equal + 1);
		else
			set_type_value(&type, &value, cmd->argv[i], "");
		if (!is_valid_identifier(type))
			return (print_invalid(cmd, i, &equal, &type), 1);
		set_env_value(sh, env, type, value);
		if (equal)
			free(type);
		i++;
	}
	return (0);
}
