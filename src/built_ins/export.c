/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 01:17:33 by mel               #+#    #+#             */
/*   Updated: 2025/09/13 01:23:15 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// case for ---> export x=y
// _____________________________________________________________
// |	1st_cmd													|
// |															|
// |	argv -> ["export", "x=y", NULL] OR ["export", "x=" "y"]	|
// |	redirs -> NULL											|
// |	builtin = EXPORT										|
// |____________________________________________________________|

// x=y y					- output x="y"
// x="y y"					- output x="y y"
// x = y OR x= y OR x =y	- error

// export		- print declare -x w env variables in ascending ascii order
// export x=1	- add env var
	
void	export_print(t_env *env)
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

int	builtin_export(t_cmd *cmd, t_env *env)
{
	t_env	*current;
	t_env	*temp;
	char	*value;
	char	*type;

	current = env;
	if (cmd->argv[1] == NULL)
	{
		export_print(env);
	}
	else // assumes everything after = is value; everything before a type 
	{
		value = ft_strrchr(cmd->argv[1], '=');
		if (!value)
		{
			ft_putstr_fd("Invalid input\n", 2);
			return (1);
		}
		value = value + 1;		// skip '='
		*(value - 1)= '\0';		// replace '=' w NULL
		type = cmd->argv[1];
		// new node
		while (current->next != NULL && current->type[0] <= type[0])
		{
			current = current->next;
		}
		temp = current->next;
		current->next = malloc(sizeof(t_env));
		// ALLOCATE AAAAAAAAAA
		current->next->type = type;
		current->next->value = value;
		current->next->next = temp;
	}
	return (0);
}
