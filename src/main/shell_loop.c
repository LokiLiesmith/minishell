#include "minishell.h"

void	print_tokens(t_token *head, int last_exit_code)
{
	t_token	*current;
	int		i;

	(void)last_exit_code;

	i = 0;
	current = head;
	while (current)
	{
		printf("Token: %d\n", i);
		printf("Raw: %s\n", current->raw);
		printf("Value: %s\n", current->value);
		printf("Context: %s\n", current->context);
		printf("Type: %d\n", current->type);
		printf("----------------------\n");
		current = current->next;
		i++;
	}
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

static char	*read_until_closed_quotes(void)
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
		tokens = tokenize(input, &open_quotes);
		free_tokens(tokens);
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
	return (input);
}

int	build_pipeline(char *line, t_shell *sh)
{
	t_token	*tokens;
	bool	open_quotes;

	open_quotes = false;
	tokens = tokenize(line, &open_quotes);
	if (!tokens)
		return (-1);
	if (expand_tokens(&tokens, sh->last_exit_code) < 0)
	{
		free_tokens(tokens);
		return (-1);
	}
	sh->pipeline = parse(tokens, sh);
	if (!sh->pipeline)
	{
		free_tokens(tokens);
		return (-1);
	}
	free_tokens(tokens);
	return (0);
}


static int	execute_pipeline(t_cmd_node *pipeline, t_shell *sh)
{
	(void)pipeline;//TODO build the damn thing;
	printf("in t_shell:%d\n", sh->last_exit_code);
	return (0);
}

void	shell_loop(t_shell *sh)
{
	char	*line;
	// (void)sh;

	while (420)
	{
		line = read_until_closed_quotes();
		if (!line)
		{
			write(1, "Exit\n", 5);
			exit(sh->last_exit_code);
		}
		if (*line)
		{
			add_history(line);
			if (build_pipeline(line, sh) < 0)
			{
				sh->last_exit_code = 2;//syntax error TODO: figure out the error handling
				free(line);
				continue ;
			}
			sh->last_exit_code = execute_pipeline(sh->pipeline, sh);
			// free_pipeline(sh->pipeline);
			sh->pipeline = NULL; //HANDOFF
			// sh->last_exit_code = execute_pipeline(sh); // deref in function?
		}
		free(line);
	}
}




