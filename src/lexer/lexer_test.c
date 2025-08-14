/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:51:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/15 01:52:39 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

////////////////////////////////////////////////////////////////////////////////
//							TOKEN STRUCT	/ ENUM							  //
////////////////////////////////////////////////////////////////////////////////
// / TO DO: COPY TO HEADER

typedef enum e_token_type
{
	WORD,
	PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	bool			quote_single;
	bool			quote_double;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token_type	op;
	int				i;
	ssize_t			len;
	ssize_t			word_len;
	t_token			*head;
	t_token			*tail;
}	t_lexer;

////////////////////////////////////////////////////////////////////////////////
//							SCAN WORD										  //
////////////////////////////////////////////////////////////////////////////////
//	split? based on space and operator if not inside "" or ''
// append token
static int ft_is_operator(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

static int	ft_is_space(int c)
{
	return ((c == '\t') || c == ' ');
}

// return len of the word
ssize_t	scan_word(const char *str, size_t i)
{
	int	start;
	int	in_double_q;
	int	in_single_q;

	start = i;
	in_single_q = 0;
	in_double_q = 0;
	while (str[i])
	{
		if (!in_double_q && str[i] == '\'')
			in_single_q = !in_single_q;
		else if (!in_single_q && str[i] == '"')
			in_double_q = !in_double_q;
		else if (!in_single_q && !in_double_q)
		{
			if (ft_is_space((unsigned char)str[i]) || ft_is_operator(str[i]))
				break ;
		}
		i++;
	}
	//return -1 if open quotes at the end?
	if (in_single_q || in_double_q)
		return (-1);
	return (ssize_t)(i - start);
}

////////////////////////////////////////////////////////////////////////////////
//							SCAN OPERATOR									  //
////////////////////////////////////////////////////////////////////////////////
static int	handle_less_than(const char *str, int i, t_token_type *type)
{
	if (str[i + 1] == '<')
	{
		*type = T_HEREDOC;
		return (2);
	}
	*type = T_IN;
	return (1);
}

static int	handle_more_than(const char *str, int i, t_token_type *type)
{
	if (str[i + 1] == '>')
	{
		*type = T_APPEND;
		return (2);
	}
	*type = T_OUT;
	return (1);
}

ssize_t	scan_operator(const char *str, int i, t_token_type *type)
{
	if (str[i] == '|')
	{
		*type = PIPE;
		return (1);
	}
	else if (str[i] == '<')
		return (handle_less_than(str, i, type));
	else if (str[i] == '>')
		return (handle_more_than(str, i, type));
	return (0);
}
////////////////////////////////////////////////////////////////////////////////
//							TOKENIZE?										  //
////////////////////////////////////////////////////////////////////////////////
// TOKENIZE LOOP
// skip whitespace
// if operator(push_token based on operator)
// else its a word, and push_token with len of the word and the string
void push_token(t_token **head,t_token **tail, t_token_type type, char *start, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->type = type;
	new->value = malloc(sizeof(char) * len + 1);
	if (!new->value)
		return ;
	ft_memcpy(new->value, start, len);
	new->value[len] = '\0';
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

static void init_lexer(t_lexer *lex)
{
	lex->len = 0;
	lex->op = WORD;
	lex->i = 0;
	lex->head = NULL;
	lex->tail = NULL;
	lex->word_len = 0;
}
// static void	print_lexer(t_lexer *lex)
// {
// 	printf("token value %s\n", lex->tail->value);
// 	printf("lex->len: %zd\n", lex->len);
// 	printf("lex->op: %d\n", lex->op);
// 	printf("lex->i: %d\n", lex->i);
// 	printf("lex->head: %p\n", lex->head);
// 	printf("lex->tail: %p\n", lex->tail);
// }

t_token	*tokenize(char *str)
{
	t_lexer	lex;

	init_lexer(&lex);
	while (str[lex.i])
	{
		while (ft_is_space(str[lex.i])) //skip whitespace
			lex.i++;
		lex.len = scan_operator(str, lex.i, &lex.op);
		if (lex.len > 0) //is operator
		{
			push_token(&lex.head, &lex.tail, lex.op, str + lex.i, lex.len);
			lex.i += lex.len;
			continue ;
		}
		lex.word_len = scan_word(str, lex.i);
		if (lex.word_len >= 0)
		{
			push_token(&lex.head, &lex.tail, WORD, str + lex.i, lex.word_len);
			lex.i += lex.word_len;
		}
		if (lex.word_len < 0)//NEGATIVE from scan word == open quotes
			return NULL;
	}
	return (lex.head);
}

static void print_tokens(t_token *head)
{
	t_token *current;
	int		i;

	i =0;
	current = head;
	while (current)
	{
		printf("Node: %d\n", i);
		printf("Type: %d\n", current->type);
		printf("String: %s\n", current->value);
		printf("______________________\n");
		current = current->next;
		i++;
	}
}

int	main(void)
{
	char *str;
	t_token *test;

	str = "echo -n \"oh, hi mark\" > out.txt < | grep hi >> log.txt";
	printf("Test: lexer_test.c\n");
	// // printf("Test String: %s\n", str);
	// printf("Chars in first word \"%s\": %zd.\n", str, scan_word(str, 0));
	// printf("char: \"_%c_\": len:%zd.\n", str[0], scan_word(str, 0));
	// printf("char: \"_%c_\": len:%zd.\n", str[1], scan_word(str, 1));
	// printf("char: \"_%c_\": len:%zd.\n", str[2], scan_word(str, 2));
	// printf("char: \"_%c_\": len:%zd.\n", str[3], scan_word(str, 3));
	// printf("char: \"_%c_\": len:%zd.\n", str[4], scan_word(str, 4));
	// printf("char: \"_%c_\": len:%zd.\n", str[5], scan_word(str, 5));
	// printf("char: \"_%c_\": len:%zd.\n", str[6], scan_word(str, 6));
	// printf("char: \"_%c_\": len:%zd.\n", str[7], scan_word(str, 7));
	// printf("char: \"_%c_\": len:%zd.\n", str[8], scan_word(str, 8));
	// printf("char: \"_%c_\": len:%zd.\n", str[21], scan_word(str, 21)); // '"'
	// printf("char: \"_%c_\": len:%zd.\n", str[22], scan_word(str, 22)); // ' '
	// printf("char: \"_%c_\": len:%zd.\n", str[23], scan_word(str, 23)); // '>'
	// printf("char: \"_%c_\": len:%zd.\n", str[24], scan_word(str, 24)); // ' '

	// printf("\nWeird Stuff\n");
	// printf("char: \"_%c_\": len:%zd.\n", "a\"b\"c"[0], scan_word("a\"b\"c", 0)); // ' '
	// printf("char: \"_%c_\": len:%zd.\n", "a\"b\"c"[1], scan_word("a\"b\"c", 1)); // ' '
	// printf("char: \"_%c_\": len:%zd.\n", "a\"b\"c"[2], scan_word("a\"b\"c", 2)); // ' '
	// printf("char: \"_%c_\": len:%zd.\n", "a\"b\"c"[3], scan_word("a\"b\"c", 3)); // ' '
	// printf("is_space: %d, is_operator: %d\n", ft_is_space('a'), ft_is_operator('a'));
	// printf("is_operator: %d, is_operator: %d, is_operator: %d\n", ft_is_operator('<'), ft_is_operator('>'), ft_is_operator('|'));
	// printf("is_operator: %d, is_operator: %d, is_operator: %d\n", ft_is_operator('"'), ft_is_operator('\''), ft_is_operator('a'));
	// print_token_list();
	tokenize("> <");
	tokenize("Mark");
	tokenize("\'Mark | >> > out\'");
	// tokenize(str);
	test = tokenize(str);
	print_tokens(test);
	// tokenize(">>");
	// tokenize("<<");
	// tokenize("|");
	// tokenize("<");
	return (0);
}

