#include "minishell.h"

static int	ft_is_delim(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ctx_split_len(char *str, char *context, int i)
{
	int	len;

	len = 0;
	while (str[i])
	{
		if ((context[i] == '0' || context[i] == 'e') && (ft_is_delim(str[i])))
			return (len);
		i++;
		len++;
	}
	return (len);
}

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