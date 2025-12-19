/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 23:46:19 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/03 23:51:22 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_create(t_shell *sh, t_token_type type, char *start, int len)
{
	t_token	*new;

	new = gc_malloc(sh, sizeof(t_token), GC_TEMP);
	new->type = type;
	new->raw = gc_malloc(sh, (sizeof(char) * len + 1), GC_TEMP);
	ft_memcpy(new->raw, start, len);
	new->raw[len] = '\0';
	new->value = NULL;
	new->context = NULL;
	new->next = NULL;
	new->was_expanded = false;
	return (new);
}

void	token_append(t_token **head, t_token **tail, t_token *new)
{
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}
