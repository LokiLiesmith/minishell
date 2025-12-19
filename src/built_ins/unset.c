/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:59:34 by mel               #+#    #+#             */
/*   Updated: 2025/12/19 23:38:53 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ORIGINAL
// int	builtin_unset(t_cmd *cmd, t_env *env)
// {
// 	t_env	*current;
// 	t_env	*temp;
// 	int		i;

// 	current = env;
// 	i = 1;
// 	// if (cmd->argv[1] == NULL)
// 	// 	return (1);

// 	while (cmd->argv[i] != NULL)
// 	{
// 		while (current->next->next != NULL && ft_strncmp(current->next->type,
				//cmd->argv[i], ft_strlen(cmd->argv[i])))
// 			current = current->next;
// 		if (current->next->next == NULL && ft_strncmp(current->next->type,
				//cmd->argv[i], ft_strlen(cmd->argv[i])) == 0)
// 		{
// 			temp = current->next;
// 			current->next = NULL;
// 		}
// 		else if (current->next != NULL && ft_strncmp(current->next->type,
				//cmd->argv[i], ft_strlen(cmd->argv[i])) == 0)
// 		{
// 			temp = current->next->next;
// 			current->next = temp;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

#include "../../include/minishell.h"

int	builtin_unset(t_cmd *cmd, t_env **env)
{
	int		i;
	t_env	*prev;
	t_env	*curr;

	i = 1;
	curr = *env;
	prev = NULL;
	while (cmd->argv[i])
	{
		while (curr)
		{
			if (ft_strcmp(curr->type, cmd->argv[i]) == 0)
			{
				if (prev)
					prev->next = curr->next;
				else
					*env = curr->next;
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
	return (0);
}
