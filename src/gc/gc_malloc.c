/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:02 by mel               #+#    #+#             */
/*   Updated: 2025/09/07 20:50:14 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	gc_free_all(void)
// {
// 	t_gc		*gc;
// 	t_gc_node	*current;
// 	t_gc_node	*head_tmp;

	
// 	current = *head;
// 	if (current == NULL)
// 		return ;
// 	while (current != NULL)
// 	{
// 		free(current->garbage);
// 		head_tmp = current;
// 		current = current->next;
// 		free(head_tmp);
// 	}
// 	*head = NULL;
// }

void	*gc_malloc(size_t count, size_t size)
{
	t_gc_node	*node;
	static t_gc	*gc;
	void		*ptr; // ptr to allocated memory

	// allocate memory
	ptr = ft_calloc(count, size);
	if (!ptr)
		return (NULL);

	// add new pointer to the linked list
	node = ft_calloc(1, sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->garbage = ptr;
	if (gc->head == NULL)
	{
		node->next = NULL;
		gc->head = node;
		gc->tail = node;
	}
	else
	{
		node->next = gc->head;
		gc->head = node;
	}
	// node->next = *head;
	// *head = node;
	return (ptr);
}

void	gc_init(void)
{
	t_gc	*gc;

	gc = get_gc();
	if (!gc)
		return ;
	gc->head = NULL;
	gc->tail = NULL;
	// gc->size = 0;
}
// int main()
// {
// 	t_gc_node	*head = NULL;
	
// 	char *test = "hello";
// 	char *test2 = "hi";
// 	char *str = gc_malloc(&head, 6);
// 	strcpy(str, test);
// 	printf("%s\n", str);
	
// 	char *str2 = gc_malloc(&head, 3);
// 	strcpy(str2, test2);
// 	printf("%s\n", str2);

// 	gc_malloc(&head, sizeof(t_gc_node));
// 	int *a = gc_malloc(&head, sizeof(int));
//     *a = 42;
	
// 	printf("%i\n", *a);
	
// 	gc_free_all(&head);
// }