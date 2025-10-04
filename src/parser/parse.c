/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:58:13 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/04 03:27:56 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse helper 
static t_cmd_node	*new_cmd_node(t_shell *sh)
{
	t_cmd_node	*new;

	new = gc_malloc(sh, sizeof(t_cmd_node), GC_TEMP);
	if (!new)
		return (NULL);
	init_cmd_node(sh, new);
	return (new);
}

static int	check_pipe_syntax(t_token **tokens, int *err)
{
	if (*tokens && (*tokens)->type == PIPE)
	{
		if (!(*tokens)->next)
		{
			report_parse_error(NULL, err);
			return (-1);
		}
		*tokens = (*tokens)->next;
	}
	return (0);
}

t_cmd_node	*parse(t_token *tokens, t_shell *sh)
{
	t_pars		p;
	t_cmd_node	*new;

	init_parser(&p);
	while (tokens)
	{
		new = new_cmd_node(sh);
		tokens = parse_command(sh, tokens, new->cmd, &p.err);
		if (p.err)
			return (NULL);
		if (p.tail)
			p.tail->next = new;
		else
			p.head = new;
		p.tail = new;
		if (check_pipe_syntax(&tokens, &p.err) < 0)
			return (NULL);
	}
	return (p.head);
}
