/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_more_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 01:47:08 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/04 01:47:48 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exit on fatal error, allocation failed --> no sh struct
void	gc_fatal(void)
{
	write(STDERR_FILENO, "fatal error\n", 12);
	exit(EXIT_FAILURE);
}

t_gc	*gc_newnode(void *ptr, t_scope scope)
{
	t_gc	*node;

	node = malloc(sizeof(t_gc));
	if (!node)
		gc_fatal();
	node->ptr = ptr;
	node->scope = scope;
	node->next = NULL;
	return (node);
}
