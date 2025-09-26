#include "minishell.h"

static t_token_type	detect_type(char *value)
{
	if (!value || !*value)
		return WORD;
	if (!ft_strcmp(value, "|"))
		return PIPE;
	if (!ft_strcmp(value, ">"))
		return T_OUT;
	if (!ft_strcmp(value, "<"))
		return T_IN;
	if (!ft_strcmp(value, ">>"))
		return T_APPEND;
	if (!ft_strcmp(value, "<<"))
		return T_HEREDOC;
	return WORD;
}

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
	new->type = detect_type(new->value);
	new->raw = old->raw;	//Sharing pointer, since GC will free?
	new->was_expanded = true;
	new->next = NULL;
	printf("[split] '%s'\n", new->value);
	return (new);
}


void splice_list(t_token **splice_node, t_token **new_h, t_token **new_t)
{
    t_token *old_next;
    t_token *tail;

    if (!splice_node || !*splice_node || !new_h || !*new_h)
        return;

    // figure out tail if not passed in
    tail = (new_t && *new_t) ? *new_t : *new_h;
    while (tail->next)
        tail = tail->next;

    old_next = (*splice_node)->next;

    // replace current node with new head
    *splice_node = *new_h;

    // connect tail to old_next
    tail->next = old_next;
}


// void	splice_list(t_token **splice_node, t_token **new_h, t_token **new_t)
// {
// 	t_token	**link;
// 	t_token	*next;

// 	if (!splice_node || !*splice_node || !new_h || !*new_h)
// 		return ;

// 	printf("start of splice list\n");
// 	link = splice_node;
// 	printf("link = splice_node\n");

// 	next = (*link)->next;
// 	printf("next = (*link)->next;\n");

// 	*link = *new_h;
// 	printf("*link = *new_h;\n");
// 	(*new_t)->next = next;
// 	printf("(*new_t)->next = next;\n");
// }

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

	if (!t || !*t || !(*t)->value || !(*t)->context)
		return (0);
	init_splice_vars(&s, t);
	while (s.old && s.old->value[s.i])
	{
		s.len = ctx_split_len(s.old->value, s.old->context, s.i);
		if (s.len > 0)
		{
			new = ctx_new_token(sh, s.old, s.i, s.len);
			if (!new)
				return (-1);
			if (new->value[0] != '\0')
				token_append(&s.new_head, &s.new_tail, new);
			s.i += s.len;
		}
		else
			s.i++;
	}
	if (!s.new_head || !s.new_tail)
		return (0);
	splice_list(t, &s.new_head, &s.new_tail);
	return (0);
}
