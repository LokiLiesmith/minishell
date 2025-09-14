#include "minishell.h"

void	init_cmd_node(t_cmd_node *node)
{
	node->cmd.argv = NULL;
	node->cmd.redirs = NULL;
	node->next = NULL;
}

void init_parser(t_pars *p)
{
	p->head = NULL;
	p->tail = NULL;
	p->err = 0;
}

static t_token *parse_command(t_token *tokens, t_cmd *cmd, int *err)
{
	*err = 0;
	while (tokens)
	{
		if (tokens->type == WORD)
			handle_word_token(tokens, cmd, err);
		if (tokens->type == T_IN)
			handle_redir_token(tokens, cmd, err);
		if (err)
			return (NULL);
		tokens = tokens->next;
	}
	// loop tru, stop at pipe or NULL
	// push WORDs into argv
	// handle redirs
	// set err = 1 and return NULL on syntax error
	return (tokens);
}

t_cmd_node	*parse(t_token *tokens, t_shell *sh)
{
	t_pars p;
	t_cmd_node	*new;

	init_parser(&p);
	while (tokens)
	{
		new = malloc(sizeof(t_cmd_node));
		if (!new)
			return (free_pipeline(p.head), NULL);
		init_cmd_node(new);
		tokens = parse_command(tokens, &new->cmd, &p.err);
		if (p.err)
			return (free_pipeline(p.head), NULL);
		if (!p.head)
			p.head = new;
		else
			p.tail->next = new;
		p.tail = new;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (p.head);
}

void	print_syntax_error(const char *unexpected)
{
	if (!unexpected || *unexpected == '\0')
		fprintf(stderr, "syntax error: unexpected token near 'newline'\n");
	else
		fprintf(stderr, "syntax error: near unexpected token %s\n", unexpected);
}
