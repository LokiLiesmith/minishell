#include "minishell.h"


int fill_ctx_token(t_token *new, int i, int len, t_token *old)
{
	new->value = ft_calloc(len + 1, sizeof(char));
	new->context = ft_calloc(len + 1, sizeof(char));
	if (!new->value || !new->context)
	{
		free(new->value);
		free(new->context);
		return (-1);
	}
	ft_memcpy(new->value, old->value + i, len);
	ft_memcpy(new->context, old->context + i, len);
	new->value[len] = '\0';
	new->context[len] = '\0';
	new->type = WORD;
	new->raw = ft_strdup(old->raw);
	if(!new->raw)
		return(-1);
	new->was_expanded = true;
	new->next = NULL;
	return (0);
}

int	ctx_push_token(t_token **h, t_token **tail, t_token *old, int i, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if(!new)
		return (-1);
	if (fill_ctx_token(new, i, len, old) < 0)
	{
		free(new);
		return (-1);
	}
	// printf("Pushed token: \"%s\", was_expanded: %d\n", new->value, new->was_expanded);
	if (*h == NULL)
	{
		*h = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
	return (0);
}

void	splice_token_list(t_token **splice_node, t_token **new_head, t_token **new_tail)
{
	t_token **link;
	t_token *next;
	
	link = splice_node;
	
	next = (*link)->next;
	*link = *new_head;
	(*new_tail)->next = next;
}

void	ctx_split_to_list(t_token **t)
{
	int		i;
	int 	len;

	t_token *old = *t;
	t_token *new_head = NULL;
	t_token *new_tail = NULL;

	// print_tokens(old, 0);
	i = 0;
	len = 0;
	while(old->value[i])
	{
		len = ctx_split_len(old->value, old->context, i);
		if (len > 0)
		{
			if (ctx_push_token(&new_head, &new_tail, old, i, len) < 0)
			{
				free_list(new_head);
				return ;
			}
			i += len;
		}
		else
			i++;
	}
	// printf("\n\n\n");
	// printf("NEW TAIL\n");
	// print_tokens(new_tail, 010);
	// printf("HEAD OF NEW LIST\n");
	// print_tokens(new_head, 010);
	// printf("OLD HEAD\n");
	// print_tokens(*t, 010);
	// printf("\n\n\n");
	splice_token_list(t, &new_head, &new_tail);
	// printf("Spliced in list, starting at: %s\n", old->value);
	free_token(old);
	free(old);
	// after splice_token_list
	// print_tokens(*t, 01);
}
