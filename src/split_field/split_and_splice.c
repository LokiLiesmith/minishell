#include "minishell.h"

t_token	*ctx_new_token(t_shell *sh, const t_token *old, int start, int len)
{
	t_token	*new;

	new = gc_malloc(sh, sizeof(*new), GC_TEMP);
	if (!new)
		return (NULL);
	new->value = gc_calloc(sh, len + 1, sizeof(char), GC_TEMP);
	new->context = gc_calloc(sh, len + 1, sizeof(char), GC_TEMP);
	if (!new->value || !new->context)
		return (NULL);
	ft_memcpy(new->value, old->value + start, len);
	ft_memcpy(new->context, old->context + start, len);
	new->value[len] = '\0';
	new->context[len] = '\0';
	new->type = WORD;
	new->raw = old->raw;	//Sharing pointer, since GC will free?
	new->was_expanded = true;
	new->next = NULL;
	return (new);
}

void	splice_list(t_token **splice_node, t_token **new_h, t_token **new_t)
{
	t_token	**link;
	t_token	*next;

	link = splice_node;

	next = (*link)->next;
	*link = *new_h;
	(*new_t)->next = next;
}

static void	init_splice_vars(t_splice *s, t_token **t)
{
	s->i = 0;
	s->len = 0;
	s->old = *t;
	s->new_head = NULL;
	s->new_tail = NULL;
}

int	ctx_split_to_list(t_shell *sh, t_token **t)
{
	t_splice	s;
	t_token		*new;

	init_splice_vars(&s, t);

	while (s.old->value[s.i])
	{
		s.len = ctx_split_len(s.old->value, s.old->context, s.i);
		if (s.len > 0)
		{
			new = ctx_new_token(sh, s.old, s.i, s.len);
			if (!new)
				return (-1);
			token_append(&s.new_head, &s.new_tail, new);
			s.i += s.len;
		}
		else
			s.i++;
	}
	splice_list(t, &s.new_head, &s.new_tail);
	return (0);
}
