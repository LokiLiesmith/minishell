#include "minishell.h"

static int	ft_is_delim(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

//TODO <25
int	ctx_split_len(char *str, char *context, int i)
{
	int	len;

	if (!str || !str[i])
		return (0);
	if ((context[i] == '0' || context[i] == 'e') && ft_is_delim(str[i]))
	{
		while (str[i] && (context[i] == '0' || context[i] == 'e')
			&& ft_is_delim(str[i]))
				i++;
			return (0);
	}
	if ((context[i] == '0' || context[i] == 'e') && is_operator(str[i]))
		{
			if (str[i] == '>' && str[i + 1] =='>')
				return (2);
			if (str[i] == '<' && str[i + 1] =='<')
				return (2);
			return (1);
		}
	len = 0;
	while (str[i + len])
	{
		if ((context[i + len] == '0' || context[i + len] == 'e'))
		{
			if (ft_is_delim(str[i + len]) || is_operator(str[i + len]))
				break;
		}
		len++;
	}
	return (len);
}
