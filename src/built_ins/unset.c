/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:59:34 by mel               #+#    #+#             */
/*   Updated: 2025/09/07 20:31:34 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// go through the args to unset vars

void	builtin_unset(t_cmd *cmd, t_env **env)
{
	t_env	*current;
	t_env	*temp;
	int		i;

	current = *env;
	i = 0;
	if (cmd->argv[1] == NULL)
		return ;
	while (cmd->argv[i] != NULL)
	{
		while (ft_strncmp(current->next->type, cmd->argv[i], ft_strlen(cmd->argv[i]))
			&& current->next != NULL)
		{
			current = current->next;
		}
		if (ft_strncmp(current->next->type, cmd->argv[i], ft_strlen(cmd->argv[i])) == 0)
		{
			temp = current->next;
			current->next = temp->next;
			// free(temp->type); free(temp->value); free(temp);
		}
		i++;
	}
}
