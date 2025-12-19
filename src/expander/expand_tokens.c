/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:32:15 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/03 22:04:27 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_expansion(t_shell *sh, t_token *curr, int *exp_len);
static void	advance_link(t_token ***link, t_token *curr);

int	expand_tokens(t_shell *sh, t_token **head)
{
	int		exp_len;
	t_token	**link;
	t_token	*curr;

	link = head;
	while (*link)
	{
		curr = *link;
		if (curr->type == WORD)
		{
			if (handle_expansion(sh, curr, &exp_len) < 0)
				return (-1);
			if (ctx_split_to_list(sh, link) < 0)
				return (-1);
			advance_link(&link, curr);
		}
		else
			link = &(*link)->next;
	}
	return (0);
}

static int	handle_expansion(t_shell *sh, t_token *curr, int *exp_len)
{
	*exp_len = expansion_len(sh, curr->raw);
	if (*exp_len < 0)
		return (-1);
	if (expand_and_strip(sh, curr, *exp_len) < 0)
		return (-1);
	return (0);
}

static void	advance_link(t_token ***link, t_token *curr)
{
	if (**link && (**link)->was_expanded)
	{
		while (**link && (**link)->was_expanded)
			*link = &(**link)->next;
	}
	else
		*link = &curr->next;
}
