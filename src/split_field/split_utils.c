#include "minishell.h"

static int	ft_is_delim(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	ctx_split_len(char *str, char *context, int i)
{
	int	len;

	if (!str || !str[i])
		return (0);
	if ((context[i] == '0' || context[i] == 'e') && ft_is_delim(str[i]))
		return (0);
	if ((context[i] == '0' || context[i] == 'e') && is_operator(str[i]))
		return (1);
	len = 0;
	while (str[i + len])
	{
		if ((context[i + len] == '0' || context[i + len] == 'e')
			&& (ft_is_delim(str[i + len]) || is_operator(str[i + len])))
			break;
		len++;
	}
	return (len);
}


// int	ctx_split_len(char *str, char *context, int i)
// {
// 	int	len;

// 	len = 0;
// 	while (str[i])
// 	{
// 		if ((context[i] == '0' || context[i] == 'e') && (ft_is_delim(str[i])))
// 			return (len);
// 		i++;
// 		len++;
// 	}
// 	return (len);
// }

/*
** Returns the length of the next token starting at str[i].
** - Whitespace just terminates a token (not part of any token).
** - Operators like | < > & are always their own single-character token.
** - Otherwise, consumes characters until next delimiter or operator.
*/



// void free_list(t_token *head)
// {
// 	t_token *curr;
// 	t_token *next;

// 	curr = head;
// 	while (curr)
// 	{	
// 		next = curr->next;
// 		free_token(curr);
// 		free(curr);
// 		curr = next;
// 	}
// }

// void 	free_token(t_token *t)
// {
// 	if(t->raw)
// 		free(t->raw);
// 	if(t->value)
// 		free(t->value);
// 	if(t->context)
// 		free(t->context);
// }