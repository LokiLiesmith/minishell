/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:59:06 by mel               #+#    #+#             */
/*   Updated: 2025/09/07 01:19:21 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(t_cmd *cmd, t_env **env)
{
	t_env	*current;

	current = *env;
	if (cmd->argv[1] != NULL)
	{
		ft_putstr_fd("Invalid command\n", 2);
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
