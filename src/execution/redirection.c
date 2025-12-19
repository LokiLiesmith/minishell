/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:02:53 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/03 22:27:46 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	t_redir_node	*current;

	current = cmd->redirs;
	while (current)
	{
		if (redirect(current))
			return (1);
		current = current->next;
	}
	return (0);
}
