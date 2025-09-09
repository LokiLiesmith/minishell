/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_field_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:35:37 by mrazem            #+#    #+#             */
/*   Updated: 2025/09/09 02:46:24 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *head, int last_exit_code)
{
	t_token *current;
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
	char *tmp;
	char *joined;

	tmp = ft_strjoin(input, "\n");
	free(input);
	joined = ft_strjoin(tmp, line);
	free(tmp);
	free(line);
	return (joined);
}
void free_tokens(t_token *token)
{
	t_token *temp;
	
	while (token)
	{
		temp = token->next;
		if (token->value)
			free(token->value);
		if (token->raw)
			free(token->raw);
		if (token->context)
			free(token->context);
		free(token);
		token = temp;
	}
}

static char *read_until_closed_quotes(void)
{
	char	*input;
	char 	*line;
	bool	open_quotes;
	t_token	*tokens;

	open_quotes = false;
	input = readline("whiskersh$ ");
	if (!input)
		return(NULL);
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

// READLINE
int	main(void)
{
	char	*input;
	t_token *tokens;
	// t_token	**tokens_ref;
	int		last_exit_code;
	
	last_exit_code = 0123;

	while (1)
	{
		input = read_until_closed_quotes();
		if (!input)
		{
			printf("=^.^=\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = tokenize(input, NULL);
		if (!tokens)
		{
			free(input);
			input = NULL;
		}
		expand_tokens(&tokens, last_exit_code);
		print_tokens(tokens, last_exit_code);
		printf("====main tokens end=====\n\n");

		free_tokens(tokens);
		free(input);
	}
	rl_clear_history();
	return (0);
}
