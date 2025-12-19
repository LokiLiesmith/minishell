/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:57:52 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/04 02:17:07 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_fd(t_redir_type t)
{
	if (t != R_HEREDOC)
		return (-1);
	return (0);
}

static bool	token_is_quoted(t_token *t)
{
	int	i;

	if (!t || !t->context)
		return (false);
	i = 0;
	while (t->context[i])
	{
		if (t->context[i] == 'd' || t->context[i] == 's')
			return (true);
		i++;
	}
	return (false);
}

//Handle token, advance 2(first valuable nextnode)
int	handle_redir_token(t_shell *sh, t_token **t, t_cmd *cmd, int *err)
{
	t_redir_node	*new;

	if (!(*t)->next || (*t)->next->type != WORD)
		return (report_parse_error((*t)->next, err), -1);
	new = gc_malloc(sh, sizeof(t_redir_node), GC_TEMP);
	if (!new)
		return (*err = 1, -1);
	new->r.type = map_token_to_redir((*t)->type);
	if (new->r.type == R_HEREDOC)
	{
		new->r.delimiter = gc_strdup(sh, (*t)->next->value, GC_TEMP);
		new->r.heredoc_quoted = token_is_quoted((*t)->next);
	}
	else
	{
		new->r.target = gc_strdup(sh, (*t)->next->value, GC_TEMP);
		if (!new->r.target)
			return (*err = 1, -1);
	}
	new->r.fd = set_fd(new->r.type);
	new->next = NULL;
	append_redir(&cmd->redirs, new);
	*t = (*t)->next->next;
	return (0);
}

// token type into redir type
t_redir_type	map_token_to_redir(t_token_type t)
{
	if (t == T_IN)
		return (R_IN);
	if (t == T_OUT)
		return (R_OUT);
	if (t == T_APPEND)
		return (R_APPEND);
	return (R_HEREDOC);
}

void	append_redir(t_redir_node **head, t_redir_node *new)
{
	t_redir_node	*current;

	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
