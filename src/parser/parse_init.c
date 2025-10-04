/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:09:05 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/04 03:20:16 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_node(t_shell *sh, t_cmd_node *node)
{
	node->cmd = gc_malloc(sh, sizeof(t_cmd), GC_TEMP);
	node->cmd->argv = NULL;
	node->cmd->redirs = NULL;
	node->cmd->builtin = NONE;
	node->next = NULL;
}

void	init_parser(t_pars *p)
{
	p->head = NULL;
	p->tail = NULL;
	p->err = 0;
}
