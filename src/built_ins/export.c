/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 01:17:33 by mel               #+#    #+#             */
/*   Updated: 2025/09/26 21:32:13 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// x=y y					- output x="y"
// x="y y"					- output x="y y"
// x = y OR x= y OR x =y	- error

// export		- print declare -x w env variables in ascending ascii order
// export x=1	- add env var
	
static void	export_print(t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->type, 1);
		ft_putchar_fd('=', 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(current->value, 1);
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
}
static	int change_export_value(t_shell *sh, t_env *current, char *value)
{
	current->value = gc_malloc(sh, ft_strlen(value) + 1, GC_GLOBAL);
	if (!current->value)
		return (1);
	ft_strlcpy(current->value, value, ft_strlen(value) + 1);
	return (0);
}
static int	export_allocate(t_shell *sh, t_env *current, t_env *temp, char *type, char *value)
{
	current->next = gc_malloc(sh, sizeof(t_env), GC_GLOBAL);
	if (!current->next)
		return (1);
	current->next->type = gc_malloc(sh, ft_strlen(type) + 1, GC_GLOBAL);
	current->next->value = gc_malloc(sh, ft_strlen(value) + 1, GC_GLOBAL);
	if (!current->next->value || !current->next->type)
		return (1);
	ft_strlcpy(current->next->type, type, ft_strlen(type) + 1);
	ft_strlcpy(current->next->value, value, ft_strlen(value) + 1);
	current->next->next = temp;
	return (0);
}

int	builtin_export(t_cmd *cmd, t_env *env, t_shell *sh)
{
	t_env	*current;
	t_env	*temp;
	char	*value;
	char	*type;

	current = env;
	if (cmd->argv[1] == NULL)
		export_print(env);
	else
	{
		value = ft_strrchr(cmd->argv[1], '=');
		if (!value)
			return (ft_putstr_fd("Invalid input\n", 2), 1);
		value = value + 1;
		*(value - 1)= '\0';
		type = cmd->argv[1];
		while (current->next != NULL && current->type[0] <= type[0] && ft_strcmp(current->type, type) != 0)
			current = current->next;
		if (ft_strcmp(current->type, type) == 0)
			return (change_export_value(sh, current, value));
		temp = current->next;
		if (export_allocate(sh, current, temp, type, value))
			return (1);
	}
	return (0);
}
