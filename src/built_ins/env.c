/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:59:06 by mel               #+#    #+#             */
/*   Updated: 2025/10/03 20:18:28 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(t_cmd *cmd, t_env *env)
{
	t_env	*current;

	current = env;
	if (cmd->argv[1] != NULL)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (1);
	}
	while (current != NULL && current->type != NULL && current->value != NULL)
	{
		ft_putstr_fd(current->type, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(current->value, 1);
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
	return (0);
}
