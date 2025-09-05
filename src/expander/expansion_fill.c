#include "minishell.h"

static void	expand_and_strip(t_token *t, int last_exit_code, int exp_len);
static int	handle_dollar(t_token *t, char *str, t_exp *exp, int last_exit);
static int	handle_var_expansion(t_token *t, char *str, t_exp *exp);

static int	handle_var_expansion(t_token *t, char *str, t_exp *exp)
{
	char	*varname;
	char	*temp;
	int		k;
			
	exp->i++;
	// fetch var value
	varname = extract_varname(str, &exp->i);
	if (!varname)
		return (-1);
	temp = getenv(varname);
	// printf("getenv result: %s\n", temp);
	if (!temp)
		temp = "";
	free(varname);

	// copy var value into token_value
	k = 0;
	while (temp[k])
	{
		t->context[exp->j] = 'e';
		t->value[exp->j++] = temp[k++];
	}
	return (0);
}
static void handle_char(t_token *t, char *str, t_exp *exp)
{
	// printf("in handle_char\n");
	// t->context[exp->j] = get_context(exp->in_sq, exp->in_dq) + '0';
	t->context[exp->j] = get_context(exp->in_sq, exp->in_dq);
	t->value[exp->j++] = str[exp->i++];
}

static void	handle_error(t_token *t, t_exp *exp, int last_exit_code)
{
	int		k;
	char	*code;
	code = ft_itoa(last_exit_code);
	if (!code)
		return ;
	k = 0;
	while (code[k])
	{
		// t->context[exp->j] = get_context(exp->in_sq, exp->in_dq) + '0';
		t->context[exp->j] = get_context(exp->in_sq, exp->in_dq);
		t->value[exp->j++] = code[k++];
	}
	exp->i += 2;
	free(code);
}

static void	handle_quote(t_token *t, const char *str, t_exp *exp)
{
	// printf("handle_quote\n");
	char c = str[exp->i];

	if ((c == '\'' && !exp->in_dq) || (c == '"' && !exp->in_sq))
	{
		update_quotes(str[exp->i], &exp->in_sq, &exp->in_dq);
		exp->i++;
	}
	else
	{
		// t->context[exp->j] = get_context(exp->in_sq, exp->in_dq) + '0';
		t->context[exp->j] = get_context(exp->in_sq, exp->in_dq);
		t->value[exp->j++] = str[exp->i++];
	}
}

void	expand_tokens(t_token *head, int last_exit_code)
{
	int	exp_len;

	// printf("EXPAND_TOKENS START\n");
	while (head)
	{
		if (head->type == WORD)
		{
			// printf("EXP LEN START\n");
			exp_len = expansion_len(head->raw, last_exit_code);
			// printf("GOT LEN\n");
			expand_and_strip(head, last_exit_code, exp_len);
			//split the value string based on context of the space character.
			split_value(head);
		}
		head = head->next;
	}
}
static int	handle_dollar(t_token *t, char *str, t_exp *exp, int last_exit_code)
{
	if (str[exp->i + 1] == '?')
	{
		handle_error(t, exp, last_exit_code);
	}
	else if (is_valid_var_start(str[exp->i + 1]))
	{
		handle_var_expansion(t, str, exp);
	}
	else
		handle_char(t, str, exp);
	return 0;
}

static void	expand_and_strip(t_token *t, int last_exit_code, int exp_len)
{
	t_exp	exp;
	char	*str;

	str = t->raw;
	t->value = ft_calloc(exp_len + 1, sizeof(char));
	t->context = malloc(exp_len + 1);
	if(!t->value || !t->context)
		printf("MALLOC FAILED IN EXPAND AND STRIP\n");
	init_exp_struct(&exp);
	while (str[exp.i])
	{
		if (str[exp.i] == '\'' || str[exp.i] == '"')
			handle_quote(t, str, &exp);
		else if (!exp.in_sq && str[exp.i] == '$')
		{
			if (handle_dollar(t, str, &exp, last_exit_code) < 0)
				return ;
		}
		else
			handle_char(t, str, &exp);
	}
	t->value[exp.j] = '\0';
	t->context[exp.j] = '\0';
	// printf("%d\n", last_exit_code);
}
