/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:51:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/15 21:23:28 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// tokenize("> <");
	// tokenize("Mark");
	// tokenize("\'Mark | >> > out\'");
	// tokenize(str);
	test = tokenize(str);
	print_tokens(test);
	// tokenize(">>");
	// tokenize("<<");
	// tokenize("|");
	// tokenize("<");
	return (0);
}

