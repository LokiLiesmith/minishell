/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 01:46:19 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/04 01:46:20 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Add a pointer to the GC list
void	gc_add(t_shell *sh, void *ptr, t_scope scope)
{
	t_gc	*node;

	if (!sh)
		gc_fatal();
	if (!ptr)
		return ;
	node = gc_newnode(ptr, scope);
	node->next = sh->gc;
	sh->gc = node;
}

void	gc_remove_node(t_shell *sh, t_gc *prev, t_gc *curr, t_gc *next)
{
	if (prev)
		prev->next = next;
	else
		sh->gc = next;
	free(curr->ptr);
	free(curr);
}

//Free based on scope - GC_GLOBAL, GC_TEMP
void	gc_free_scope(t_shell *sh, t_scope scope)
{
	t_gc	*curr;
	t_gc	*prev;
	t_gc	*next;

	if (!sh)
		return ;
	prev = NULL;
	curr = sh->gc;
	while (curr)
	{
		next = curr->next;
		if (curr->scope == scope)
			gc_remove_node(sh, prev, curr, next);
		else
			prev = curr;
		curr = next;
	}
}

//GC free both scopes
void	gc_free_all(t_shell *sh)
{
	t_gc	*curr;
	t_gc	*next;

	if (!sh)
		return ;
	curr = sh->gc;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
	sh->gc = NULL;
}
