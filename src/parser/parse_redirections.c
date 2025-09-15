#include "minishell.h"

static int	set_fd(t_redir_type t)
{
	if (t == R_IN || t == R_HEREDOC)
		return (0);
	return (1);
}

//Handle token, advance 2(first valuable nextnode)
int	handle_redir_token(t_token **t, t_cmd *cmd, int *err)
{
	t_redir_node	*new;

	if (!(*t)->next || (*t)->next->type != WORD)
	{
		if (!(*t)->next)
			print_syntax_error(NULL);
		else
			print_syntax_error((*t)->next->raw);
		*err = 1;
		return (-1);
	}
	new = malloc(sizeof(t_redir_node));
	if (!new)
		return (*err = 1, -1);
	new->r.type = map_token_to_redir((*t)->type);
	new->r.target = ft_strdup((*t)->next->value);
	// if (!new->r.target)
	// {
	// 	free(new);
	// 	return (*err = 1, -1);
	// }
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
