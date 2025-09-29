/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:59:34 by mel               #+#    #+#             */
/*   Updated: 2025/09/29 19:02:56 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_unset(t_cmd *cmd, t_env *env)
{
	t_env	*current;
	t_env	*temp;
	int		i;

	current = env;
	i = 1;
	if (cmd->argv[1] == NULL)
		return (1);
	while (cmd->argv[i] != NULL)
	{
		while (current->next->next != NULL && ft_strncmp(current->next->type, cmd->argv[i], ft_strlen(cmd->argv[i])))
			current = current->next;
		if (current->next->next == NULL && ft_strncmp(current->next->type, cmd->argv[i], ft_strlen(cmd->argv[i])) == 0)
		{
			temp = current->next;
			current->next = NULL;
		}
		else if (current->next != NULL && ft_strncmp(current->next->type, cmd->argv[i], ft_strlen(cmd->argv[i])) == 0)
		{
			temp = current->next->next;
			current->next = temp;
		}
		else if (current->next->next == NULL && ft_strncmp(current->next->type, cmd->argv[i], ft_strlen(cmd->argv[i])))
			return (ft_putstr_fd("unset: not a valid identifier\n", 2), 1);
		i++;
	}
	return (0);
}
