/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 02:12:51 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/04 02:16:28 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*report_parse_error(t_token *token, int *err)
{
	*err = 1;
	if (token)
	{
		if (token->raw && *token->raw)
			fprintf(stderr, "syntax error near unexpected token `%s`\n",
				token->raw);
		else
			fprintf(stderr, "syntax error near unexpected token `newline`\n");
	}
	else
		fprintf(stderr, "syntax error near unexpected token `newline`\n");
	return (NULL);
}

int	is_quoted_empty(t_token *token)
{
	if (!token || !token->value)
		return (0);
	if (token->value[0] != '\0')
		return (0);
	if (token->context && (token->context[0] == 's'
			|| token->context[0] == 'd'))
		return (1);
	return (0);
}
