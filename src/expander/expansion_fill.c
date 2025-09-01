#include "minishell.h"

void	expand_tokens(t_token *head, int last_exit_code)
{
	int	exp_len;

	while (head)
	{
		if (head->type == WORD)
		{
			exp_len = expansion_len(head, last_exit_code);
			expand_and_strip(head, last_exit_code, exp_len);
		}
		head = head->next;
	}
}

void	expand_and_strip(t_token *t, int last_exit_code, int exp_len)
{
	t_exp	exp;
	char	*str;

	str = t->value;
	t->value = malloc(sizeof(char) + (exp_len + 1));
	t->context = malloc(sizeof(char) * (exp_len + 1));
	init_exp_struct(&exp);
	while (str[exp.i])
	{
		if (str[exp.i] == '\'' || '"')
			handle_quote(str, &exp);
		else if (!exp.in_sq && str[exp.i] == '$')
		{
			if (handle_dollar(str, &exp, last_exit_code) < 0)
				return (-1);
		}
		else
			handle_char(&exp);
	}
}
