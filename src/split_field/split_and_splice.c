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
	new->raw = ft_strdup("expanded");
	if (!new->raw)
	{
		free(new->value);
		free(new->context);
		return(-1);
	}
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

void splice_token_list(t_token **link_to_old, t_token *new_head, t_token* new_tail)
{
	t_token *old = *link_to_old;
	t_token *next = old->next;
    printf("splice_token_list start\n");
        
	if (new_head == NULL)
	{
    	free_token(old);
    	free(old);
    	printf("splice_token_list after free\n");
        printf("in if\n");
		*link_to_old = next;
        printf("next\n");
		return ;
	}
    printf("link_to_old%p\n", link_to_old);
    printf("new_head%p\n", new_head);
    *link_to_old = new_head;
    printf("new_head\n");

    new_tail->next = next;
    printf("splice_token_list finished\n");

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
	splice_token_list(&old, new_head, new_tail);
}
