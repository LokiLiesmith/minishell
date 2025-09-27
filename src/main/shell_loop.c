#include "minishell.h"

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
		line = readline("> ");
		if (!line)
		{
			free(input);
			return (NULL);
		}
		input = append_line(input, line);
	}
	(void)tokens;
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
			return (-1);
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


// static int	execute_pipeline(t_cmd_node *pipeline, t_shell *sh)
// {
// 	// (void)pipeline;//TODO build the damn thing;
// 	print_pipeline(pipeline);
// 	printf("in t_shell:%d\n", sh->last_exit_code);
// 	printf("HANDOFF SUCCESSFUL!\n");
// 	return (0);
// }

static void	handle_exit(t_shell *sh)
{
	write(1, "Exit\n", 5);
	gc_free_all(sh);
	exit(sh->last_exit_code);
}

static void handle_command(char *line, t_shell *sh)
{
	add_history(line);
	if (build_pipeline(line, sh) < 0)
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
		sh->last_exit_code = execute_start(sh->pipeline, sh);
		sh->pipeline = NULL;
}

void	shell_loop(t_shell *sh)
{
	char	*line;

	while (420)
	{
		line = read_until_closed_quotes(sh);
		if (!line)
			handle_exit(sh);
		if (*line)
			handle_command(line, sh);
		free(line);
		gc_free_scope(sh, GC_TEMP);
	}
}




