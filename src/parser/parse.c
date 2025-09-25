#include "minishell.h"

void	init_cmd_node(t_cmd_node *node)
{
	node->cmd.argv = NULL;
	node->cmd.redirs = NULL;
	node->next = NULL;
}

void	init_parser(t_pars *p)
{
	p->head = NULL;
	p->tail = NULL;
	p->err = 0;
}

static char	**convert_arglist(t_shell *sh, t_strlist *list)
{
	int			count;
	t_strlist	*tmp;
	char		**argv;
	int			i;

	tmp = list;
	count = 0;
	while (tmp)
	{
		count ++;
		tmp = tmp->next;
	}
	argv = gc_malloc(sh, (sizeof(char *) * (count + 1), GC_TEMP));
	if (!argv)
		return (NULL);
	tmp = list;
	i = 0;
	while (i < count)
	{
		argv[i++] = tmp->str;//reusing string
		tmp = tmp->next;
	}
	argv[count] = NULL;
	return (argv);
}

t_token	*parse_command(t_shell *sh, t_token *tokens, t_cmd *cmd, int *err)
{
	t_strlist	*arglist;

	arglist = NULL;
	*err = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
		{
			if (handle_word_tkn(sh, tokens, err, &arglist) < 0)
				return (NULL);
			tokens = tokens->next; // advance after WORD
			continue ;
		}
		else if (tokens->type == T_IN || tokens->type == T_OUT
			|| tokens->type == T_APPEND || tokens->type == T_HEREDOC)
		{
			if (handle_redir_token(&tokens, cmd, err) < 0)
				return (NULL);
			continue ;
		}
		print_syntax_error(tokens->raw);
		*err = 1;
		return (NULL);
	}
	cmd->argv = convert_arglist(sh, arglist);  // arglist (not &arglist)
	cmd->builtin = get_builtin_type(cmd->argv ? cmd->argv[0] : NULL);
	return (tokens);
}


t_builtin get_builtin_type(char *s)
{
	if (!s)
		return (NONE);
	if (!ft_strcmp(s, "echo"))//if  0 == match
		return (ECHO);
	if (!ft_strcmp(s, "cd"))
		return (CD);
	if (!ft_strcmp(s, "pwd"))
		return (PWD);
	if (!ft_strcmp(s, "export"))
		return (EXPORT);
	if (!ft_strcmp(s, "unset"))
		return (UNSET);
	if (!ft_strcmp(s, "env"))
		return (ENV);
	if (!ft_strcmp(s, "exit"))
		return (EXIT);
	return (NONE);
}

// gather all WORD tokens into a LL
int	handle_word_tkn(t_shell *sh, t_token *t, int *err, t_strlist **arglist)
{
	t_strlist	*new;
	t_strlist	*current;

	new = gc_malloc(sh, sizeof(t_strlist), GC_TEMP);
	if (!new || !t->value)
		return (*err = 1, -1);
	new->str = t->value;
	new->next = NULL;
	if (!*arglist)
		*arglist = new;
	else
	{
		current = *arglist;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}

t_cmd_node	*parse(t_token *tokens, t_shell *sh)
{
	t_pars		p;
	t_cmd_node	*new;

	init_parser(&p);
	while (tokens)
	{
		new = gc_malloc(sh, sizeof(t_cmd_node), GC_TEMP);
		// if (!new)
		// 	return (free_pipeline(p.head), NULL);
		init_cmd_node(new);
		tokens = parse_command(tokens, &new->cmd, &p.err);
		if (p.err)
			return (NULL);
		if (!p.head)
			p.head = new;
		else
			p.tail->next = new;
		p.tail = new;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	fprintf(stderr, "error code:%d\n", sh->last_exit_code);
	return (p.head);
}


void	print_syntax_error(const char *unexpected)
{
	if (!unexpected || *unexpected == '\0')
		fprintf(stderr, "syntax error: unexpected token near 'newline'\n");
	else
		fprintf(stderr, "syntax error: near unexpected token %s\n", unexpected);
}
