/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:51:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/12 11:36:31 by mrazem           ###   ########.fr       */
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
	struct t_token	*next;
}	t_token;

/////////////////////////////////////////////////////////////////////////////////

//	split? based on space and operator if not inside "" or ''
// append token
int	static ft_is_operator(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

static int	ft_is_space(int c)
{
	return ((c == '\t') || c == ' ');
}
// return len of the word
static int scan_word(const char *str, size_t i)
{
	int start;
	int in_double_q;
	int in_single_q;

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
			if (ft_is_space(str[i]) || ft_is_operator(str[i]))
				break;
		}
		i++;
	}
	//return -1 if open quotes at the end?
	if (in_single_q || in_double_q)
		return (-1);
	return (i - start);
}
// static int tokenize(char *str)
// {
// 	while (*str)
// 	{
// 		if (ft_is_operator(*str))
// 		{
// 			if (*str == '<')
// 				if (*(str + 1) == '<')
// 				{
// 					append_token(type = T_HEREDOC);
// 					str++;
// 				}
// 				else
// 					append_token(type = T_IN);
// 				str++;
// 			if (*str == '>')
// 			{
// 				if (*(str + 1) == '>')
// 				{
// 					append_toke(type = T_APPEND);
// 					str++;
// 				}
// 				else
// 					append_token(type = T_OUT);
// 			}
// 		}
// 	}
// }

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

int	scan_operator(const char *str, int i, t_token_type *type)
{
	if (str[i] == '|')
	{
		*type = PIPE;
		return (1);
	}
	else if (str[i] == '<')
		return (handle_less_than(str, i, type));
	else if(str[i] == '>')
		return (handle_more_than(str, i, type));
	return (0);
}

// TOKENIZE LOOP
// skip whitespace
// if operator(push_token based on operator)
// else its a word, and push_token with len of the word and the string
// int	tokenize(char *str)
// {
// 	// alloc head node
// 	// t_token	*token;
// 	int	i;

// 	while (*str)
// 	{
// 		while(ft_is_space(*str)) //skip whitespace
// 			str++;
// 		i = 0;
// 		if (ft_is_operator(str[i])) //if operator, push node; len = scan_operator(str, i, &type)
// 		{
// 			scan_operator(str)
// 			push_token()
// 		}
// 		else	//ELSE ITS A WORD
// 	}
// }

int	main(void)
{
	char *str;

	str = "echo -n \"oh, hi mark\" > out.txt < | grep hi >> log.txt";
	printf("Test: lexer_test.c\n");
	// printf("Test String: %s\n", str);
	printf("Chars in first word \"%s\": %d.\n", str, scan_word(str, 0));
	printf("char: \"_%c_\": len:%d.\n", str[0], scan_word(str, 0));
	printf("char: \"_%c_\": len:%d.\n", str[1], scan_word(str, 1));
	printf("char: \"_%c_\": len:%d.\n", str[2], scan_word(str, 2));
	printf("char: \"_%c_\": len:%d.\n", str[3], scan_word(str, 3));
	printf("char: \"_%c_\": len:%d.\n", str[4], scan_word(str, 4));
	printf("char: \"_%c_\": len:%d.\n", str[5], scan_word(str, 5));
	printf("char: \"_%c_\": len:%d.\n", str[6], scan_word(str, 6));
	printf("char: \"_%c_\": len:%d.\n", str[7], scan_word(str, 7));
	printf("char: \"_%c_\": len:%d.\n", str[8], scan_word(str, 8));
	printf("char: \"_%c_\": len:%d.\n", str[21], scan_word(str, 21)); // '"'
	printf("char: \"_%c_\": len:%d.\n", str[22], scan_word(str, 22)); // ' '
	printf("char: \"_%c_\": len:%d.\n", str[23], scan_word(str, 23)); // '>'
	printf("char: \"_%c_\": len:%d.\n", str[24], scan_word(str, 24)); // ' '

	printf("\nWeird Stuff\n");
	printf("char: \"_%c_\": len:%d.\n", "a\"b\"c"[0], scan_word("a\"b\"c", 0)); // ' '
	printf("char: \"_%c_\": len:%d.\n", "a\"b\"c"[1], scan_word("a\"b\"c", 1)); // ' '
	printf("char: \"_%c_\": len:%d.\n", "a\"b\"c"[2], scan_word("a\"b\"c", 2)); // ' '
	printf("char: \"_%c_\": len:%d.\n", "a\"b\"c"[3], scan_word("a\"b\"c", 3)); // ' '
	printf("is_space: %d, is_operator: %d\n", ft_is_space('a'), ft_is_operator('a'));
	printf("is_operator: %d, is_operator: %d, is_operator: %d\n", ft_is_operator('<'), ft_is_operator('>'), ft_is_operator('|'));
	printf("is_operator: %d, is_operator: %d, is_operator: %d\n", ft_is_operator('"'), ft_is_operator('\''), ft_is_operator('a'));
	// print_token_list();
	return (0);
}

