#include "minishell.h"

void init_cmd_node(t_shell *sh, t_cmd_node *node)
{
    node->cmd = gc_malloc(sh, sizeof(t_cmd), GC_TEMP);
    node->cmd->argv    = NULL;
    node->cmd->redirs  = NULL;
    node->cmd->builtin = NONE;
    node->next = NULL;
}

void	init_parser(t_pars *p)
{
	p->head = NULL;
	p->tail = NULL;
	p->err = 0;
}

static char	**convert_arglst(t_shell *sh, t_strlist *list)
{
	t_strlist	*tmp;
	char		**argv;
	int			i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	argv = gc_malloc(sh, (sizeof(char *) * (i + 1)), GC_TEMP);
	if (!argv)
		return (NULL);
	i = 0;
	while (list)
	{
		argv[i] = list->str;
		if (argv[i][0] == '\0')
            printf("[argv %d] quoted-empty token: ''\n", i);
        else
            printf("[argv %d] '%s'\n", i, argv[i]);
		i++;
		list = list->next;
	}
	argv[i] = NULL;
	return (argv);
}

static int	is_redir_token(t_token_type type)
{
	return (type == T_IN || type == T_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

t_token *report_parse_error(t_token *token, int *err)
{
    *err = 1;
    if (token)
        fprintf(stderr,
            "syntax error near unexpected token `%s`\n",
            token->raw && *token->raw ? token->raw : "newline");
    else
        fprintf(stderr,
            "syntax error near unexpected token `newline`\n");
    return NULL;
}

static void	set_builtin(t_cmd *cmd)
{
	char	*first;

	first = NULL;
	if (cmd->argv)
		first = cmd->argv[0];
	cmd->builtin = get_builtin_type(first);
}
//TODO REFACTOR <25
t_token	*parse_command(t_shell *sh, t_token *tokens, t_cmd *cmd, int *err)
{
	t_strlist	*arglst;

	arglst = NULL;
	*err = 0;
	if (!tokens)
	{
		*err = 0;//GPT?
		return (NULL);
	}
	if (tokens->type == PIPE)
		return (report_parse_error(tokens, err));
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
		{
			if (handle_word_tkn(sh, &tokens, err, &arglst) < 0)
				return (NULL);
		}
		else if (is_redir_token(tokens->type))
		{
			if (handle_redir_token(sh, &tokens, cmd, err) < 0)
				return (NULL);
		}
		else
			return (report_parse_error(tokens, err));
	}
	cmd->argv = convert_arglst(sh, arglst);  // arglst (not &arglst)
	set_builtin(cmd);
	return (tokens);
}

// strcmp = 0, if match found.
t_builtin get_builtin_type(char *s)
{
	if (!s)
		return (NONE);
	if (!ft_strcmp(s, "echo"))
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

int	is_quoted_empty(t_token *token)
{
	if (!token || !token->value)
		return (0);
	if (token->value[0] != '\0')
		return (0);
	if (token->context && (token->context[0] == 's' || token->context[0] == 'd'))
		return (1);
	return (0);
}
//TODO <25
// gather all WORD tokens into a LL
int	handle_word_tkn(t_shell *sh, t_token **t, int *err, t_strlist **arglst)
{
	t_strlist	*new;
	t_strlist	*current;
	t_token		*token;

	token = *t;
	if (token->value[0] == '\0' && !is_quoted_empty(token))
	{
		*t = token->next;
		return 0;
	}
	new = gc_malloc(sh, sizeof(t_strlist), GC_TEMP);
	if (!new || !token || !token->value)
		return (*err = 1, -1);
	new->str = token->value;
	new->next = NULL;
	if (!*arglst)
		*arglst = new;
	else
	{
		current = *arglst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	*t = token->next;
	return (0);
}
//TODO <25
t_cmd_node	*parse(t_token *tokens, t_shell *sh)
{
	t_pars		p;
	t_cmd_node	*new;

	init_parser(&p);
	while (tokens)
	{
		new = gc_malloc(sh, sizeof(t_cmd_node), GC_TEMP);
		init_cmd_node(sh, new);
		tokens = parse_command(sh, tokens, new->cmd, &p.err);
		if (p.err)
			return (NULL);
		if (!p.head)
			p.head = new;
		else
			p.tail->next = new;
		p.tail = new;
		if (tokens && tokens->type == PIPE)
		{
			if (!tokens->next)
			{
				report_parse_error(NULL, &p.err);
				return (NULL);
			}
			tokens = tokens->next;
		}
	}
	return (p.head);
}
