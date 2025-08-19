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

static void print_tokens(t_token *head, bool *quotes_open)
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
		printf("Open_quotes in main: %d\n", *quotes_open);
		printf("______________________\n");
		current = current->next;
		i++;
	}
}
static void	set_quote_flags(t_token *token)
{
	int 	i;
	bool	in_double_q;
	bool	in_single_q;

	in_double_q = false;
	in_single_q = false;

	i = 0;
	while(token->value[i])
	{
		if (!in_double_q && token->value[i] =='\'')
		{
			in_single_q = !in_single_q;
			token->quote_single = true;
		}
		else if (!in_single_q && token->value[i] == '\"')
		{
			in_double_q = !in_double_q;
			token->quote_double = true;
		}
		i++;
	}
	// if (in_double_q || in_single_q)
	// 	*quotes_open = true;
}

// static void strip_quotes(t_token *token)
// {
	
// }

static void	expand_tokens(t_token *head)
{
	while (head)
	{
		if (head->type == WORD)
		{
			set_quote_flags(head);
			// strip_quotes(head);
			// strip_quotes_and_set_flags(head);
			// expand_vars(head);
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

// char *expand_and_remove_quotes(char *str)
// {

// 	while (str[i])
// 	{

// 	}
// 	return (result);
// }

int main(void)
{
	char *input;
	t_token *tokens;
	bool	quotes_open;

	quotes_open = false;
	input = "echo -n \"oh, hi mark > out.txt < | \'grep\' hi >> log.txt";
	// printf("Test: expander_test.c\n");
	tokens = tokenize(input, &quotes_open);
	// print_tokens(test);
	expand_tokens(tokens);
	print_tokens(tokens, &quotes_open);
	if (quotes_open)
		printf("OPEN QUOTES!\n");
	return (0);
}

// READLINE
// int	main(void)
// {
// 	// int		quote_open;
// 	char 	*input;
// 	// t_token *tokens;
// 	t_cmd_node *cmds;

// 	input = NULL;
// 	// line = NULL;
// 	// tokens = NULL;

// 	while (1)
// 	{
// 		// quote_open = 0;
// 		input = readline("whiskersh$ ");
// 		if (!input)
// 		{
// 			printf("\n=-.-=\n");
// 			break;
// 		}
// 		if (*input)
// 			add_history(input);
// 		printf("%s\n", input);
// 		free(input);
// 	}

// 	// // input = "echo -n \"oh, hi mark\" > out.txt < | \'grep\' hi >> log.txt";
// 	// // printf("Test: expander_test.c\n");
// 	// tokens = tokenize(input);
// 	// // print_tokens(test);
// 	// expand_tokens(tokens);
// 	// print_tokens(tokens);
// 	rl_clear_history();
// 	return (0);
// }
