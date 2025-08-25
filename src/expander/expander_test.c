/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:35:37 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/08 17:54:16 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define NEW_BUFFER_SIZE 4096

char *expand_and_remove_quotes(const char *str);

static void print_tokens(t_token *head)
{
	t_token *current;
	int		i;

	i = 0;
	current = head;
	while (current)
	{
		printf("Token: %d\n", i);
		printf("Type: %d\n", current->type);
		printf("String: %s\n", current->value);
		printf("Single_quotes: %d\n", current->quote_single);
		printf("Double_quotes: %d\n", current->quote_double);
		// printf("Open_quotes in main: %d\n", *quotes_open);
		printf("______________________\n");
		current = current->next;
		i++;
	}
}
// static void	set_quote_flags(t_token *token)
// {
// 	int 	i;
// 	bool	in_double_q;
// 	bool	in_single_q;

// 	in_double_q = false;
// 	in_single_q = false;

// 	i = 0;
// 	while(token->value[i])
// 	{
// 		if (!in_double_q && token->value[i] =='\'' &&
// 			(i == 0 || token->value[i - 1] != '\\'))
// 		{
// 			in_single_q = !in_single_q;
// 			token->quote_single = true;
// 		}
// 		else if (!in_single_q && token->value[i] == '\"' &&
// 				(i == 0 || token->value[i - 1] != '\\'))
// 		{
// 			in_double_q = !in_double_q;
// 			token->quote_double = true;
// 		}
// 		i++;
// 	}
// 	// if (in_double_q || in_single_q)
// 	// 	*quotes_open = true;
// }

// static void strip_quotes(t_token *token)
// {
// 	char *src;
// 	char *dst;
// 	int i;
// 	int j;

// 	src = token->value;
// 	dst = malloc(ft_strlen(src) + 1);
// 	i = 0;
// 	j = 0;
// 	if (!dst)
// 		return ;
// 	while (src[i])
// 	{
// 		if (token->quote_single && src[i] == '\'')
// 			i++;
// 		else if (token->quote_double && src[i] == '\"')
// 			i++;
		// else if (token->quote_double && src[i] == '\\' &&
		// 	(src[i + 1] == '"' || src[i + 1] == '\\' || src[i + 1] == '$'))
// 		{
// 			i++;
// 			dst[j++] = src[i++];
// 		}
// 		else
// 			dst[j++] = src[i++];
// 	}
// 	dst[j] = '\0';
// 	free(token->value);
// 	token->value = dst;
// }

static void	expand_tokens(t_token *head)
{
	while (head)
	{
		if (head->type == WORD)
		{
			head->value = expand_and_remove_quotes(head->value);
			// set_quote_flags(head);
			// strip_quotes(head);
			// // expand_vars(head);
		}
		head = head->next;
	}
}
// check for quotes, strip them, set token flags for quotes
// void	strip_quotes_and_set_flags(t_token	*token)
// {
// 	set_quote_flags(token->value);
// }

// static bool is_var_char(char c)
// {
// 	return ((c >= 'a' && c <= 'z') ||
// 			(c >= 'A' && c <= 'Z') ||
// 			(c >= '0' && c <= '9') ||
// 			(c == '_'));
// }
// static bool is_var_start(char c)
// {
// 	return ((c >= 'a' && c <= 'z') ||
// 			(c >= 'A' && c <= 'Z') ||
// 			(c == '_'));
// }

// Walk through the input string (token->value)
// Track quote context:
// in_single_q → '...'
// in_double_q → "..." (still allow $ expansion)
// If we see $ and we are not in single quotes:
// Handle:
// $? → convert exit status
// $VAR → extract name, getenv()
// Remove all quote characters from the output
// Copy everything else into a result string
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
	// int		quotes_open;
	char	*input;
	t_token *tokens;
	int		last_exit_code;

	last_exit_code = 0;
	// t_cmd_node *cmds;
	/// GETENV, EXPAND TO "", Dont Free
	// printf("HOME: %s\n", getenv("HOME"));
	// printf("USER: %s\n", getenv("USER"));
	// printf("SHELL: %s\n", getenv("SHELL"));
	// printf("WHAT: %s\n", getenv("WHAT")); // Should be NULL

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
			free(input);
		// printf("%s\n", input);
		expand_tokens(tokens, last_exit_code);
		print_tokens(tokens);
		free_tokens(tokens);
		free(input);
	}
	rl_clear_history();
	return (0);
}

char *expand_and_remove_quotes(const char *input, int last_exit_code)
{
	bool	in_double_q;
	bool	in_single_q;
	char	*result;
	char	*code;
	size_t	i;
	size_t	j;
	int		k;

	in_single_q = false;
	in_double_q = false;
	i = 0;
	j = 0;
	k = 0;
	
	result = malloc(NEW_BUFFER_SIZE);
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_q)
		{
			in_single_q = !in_single_q;
			i++;
			continue;
		}
		else if (input[i] == '"' && !in_single_q)
		{
			in_double_q = !in_double_q;
			i++;
			continue;
		}
		else if (input[i] == '$' && !in_single_q) // EXPAND LAST_EXIT_CODE
		{
			if (input[i + 1] == '?')
			{
				code = ft_itoa(last_exit_code);
				if (!code)
					return(NULL);
				k = 0;
				while (code[k])
					result[j++] = code[k++];
				i += 2;
				free(code);
				continue ;
			}
			else if (is_valid_var_start(input[i + 1]))
			{
				//extract var name and getenv()
			}
			else
			{
				//copy literal $
			}
		}
		if (in_double_q && input[i] == '\\' &&
			(input[i + 1] == '"' || input[i + 1] == '$' || input[i + 1] == '\\'))
		{
			i++;
		}
		result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
