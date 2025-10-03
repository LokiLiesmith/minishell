#include "minishell.h"

int is_only_spaces(const char *s)
{
    int i = 0;
    while (s[i])
    {
        if (!ft_is_space((unsigned char)s[i]))
            return (0);
        i++;
    }
    return (1);
}

static char	*append_line(char *input, char *line)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(input, "\n");
	free(input);
	joined = ft_strjoin(tmp, line);
	free(tmp);
	free(line);
	return (joined);
}

static char	*read_until_closed_quotes(t_shell *sh)
{
	char	*input;
	char	*line;
	bool	open_quotes;
	t_token	*tokens;

	open_quotes = false;
	input = readline("whiskersh$ ");
	if (!input)
		return (NULL);
	while (1)
	{
		tokens = tokenize(sh, input, &open_quotes);
		gc_free_scope(sh, GC_TEMP);
		if (!open_quotes)
			break ;
		line = readline("quote> ");
		if (!line)
		{
			free(input);
			return (NULL);
		}
		input = append_line(input, line);
	}
	(void)tokens;//TODO fishy..
	return (input);
}

int	build_pipeline(char *line, t_shell *sh)
{
	t_token	*tokens;
	bool	open_quotes;

	open_quotes = false;
	tokens = tokenize(sh, line, &open_quotes);
	if (!tokens)
	{
		if (open_quotes)
		{
			return (-1);
		}
		sh->pipeline = NULL;
		return (0);
	}
	if (expand_tokens(sh, &tokens) < 0)
	{
		gc_free_scope(sh, GC_TEMP);
		return (-1);
	}
	sh->pipeline = parse(tokens, sh);
	if (!sh->pipeline)
	{
		gc_free_scope(sh, GC_TEMP);
		return (-1);
	}
	return (0);
}

static void	handle_exit(t_shell *sh)
{
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	gc_free_all(sh);
	exit(sh->last_exit_code);
}

static void handle_command(char *line, t_shell *sh)
{
	int	status;

	add_history(line);
	status = build_pipeline(line, sh);
	if (status < 0)
	{
		sh->last_exit_code = 2;
		gc_free_scope(sh, GC_TEMP);
		return ;
	}
	if (!sh->pipeline)
	{
		sh->last_exit_code = 0;
		return ;
	}
	if (prepare_heredoc(sh, sh->pipeline))
	{
		sh->pipeline = NULL;
		gc_free_scope(sh, GC_TEMP);
		return ; // returns on failure and doesnt go into execution, where the heredoc signal interrupt err code gets overwritten
	}
	sh->last_exit_code = execute_start(sh->pipeline, sh);
	sh->pipeline = NULL;
}

void	shell_loop(t_shell *sh)
{
	char	*line;

	while (420)
	{
		if (isatty(STDIN_FILENO))
			line = read_until_closed_quotes(sh);
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			handle_exit(sh);
		if (*line && !is_only_spaces(line))
			handle_command(line, sh);
		free(line);
		gc_free_scope(sh, GC_TEMP);
	}
}
