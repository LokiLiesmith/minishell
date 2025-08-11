/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:51:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/11 19:11:15 by mrazem           ###   ########.fr       */
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

//	split? based on space if not inside "" or ''
// append token
int	static ft_is_operator(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

static int	ft_is_space(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
// return len of the word
static int scan_word(char *str, int i)
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
		if (!in_single_q && str[i] == '"')
			in_double_q = !in_double_q;
		if (!in_single_q && !in_double_q)
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
	// print_token_list();
	return (0);
}

