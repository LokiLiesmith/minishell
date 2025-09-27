#include "minishell.h"

static int	expand_and_strip(t_shell *sh, t_token *t, int exp_len);

static size_t	write_exit_code(char *dst, int last_exit_code)
{
	char	buffer[12];
	long	num;
	size_t	len;
	size_t	i;
	bool	neg;

	num = last_exit_code;
	neg = num < 0;
	if (neg)
		num = -num;
	len = 0;
	if (num == 0)
		buffer[len++] = '0';
	while (num > 0)
	{
		buffer[len++] = '0' + (num % 10);
		num /= 10;
	}
	i = 0;
	if (neg)
		dst[i++] = '-';
	while (len > 0)
		dst[i++] = buffer[--len];
	return (i);
}

static int	handle_var_expansion(t_shell *sh, t_token *t, char *str, t_exp *exp)
{
	char	*varname;
	char	*temp;
	size_t	k;

	exp->i++;
	varname = extract_varname(sh, str, &exp->i);
	if (!varname)
		return (-1);
	temp = get_env_value(sh, varname);
	if (!temp)
		temp = "";
	exp->in_exp = true;
	k = 0;
	while (temp[k])
	{
		t->context[exp->j] = get_context(exp->in_sq, exp->in_dq, exp->in_exp);
		t->value[exp->j++] = temp[k++];
	}
	exp->in_exp = false;
	return (0);
}

static void	handle_char(t_token *t, char *str, t_exp *exp)
{
	t->context[exp->j] = get_context(exp->in_sq, exp->in_dq, exp->in_exp);
	t->value[exp->j++] = str[exp->i++];
}

static void	handle_error(t_token *t, t_exp *exp, t_shell *sh)
{
	size_t	written;

	exp->in_exp = true;
	written = write_exit_code(t->value + exp->j, sh->last_exit_code);
	while (written--)
	{
		t->context[exp->j] = get_context(exp->in_sq, exp->in_dq, exp->in_exp);
		exp->j++;
	}
	exp->i += 2;
	exp->in_exp = false;
}

static void	handle_quote(t_token *t, const char *str, t_exp *exp)
{
	char	c;

	c = str[exp->i];
	if ((c == '\'' && !exp->in_dq) || (c == '"' && !exp->in_sq))
	{
		update_quotes(str[exp->i], &exp->in_sq, &exp->in_dq);
		exp->i++;
	}
	else
	{
		t->context[exp->j] = get_context(exp->in_sq, exp->in_dq, exp->in_exp);
		t->value[exp->j++] = str[exp->i++];
	}
}
//TODO REFACTOR TO <25
int expand_tokens(t_shell *sh, t_token **head)
{
    int     exp_len;
    t_token **link;
	t_token *curr;

	link = head;
    while (*link)
    {
    	curr = *link;
        if (curr->type == WORD)
        {
            exp_len = expansion_len(sh, curr->raw);
            if (exp_len < 0)
                return (-1);
            if (expand_and_strip(sh, curr, exp_len) < 0)
                return (-1);
            if (ctx_split_to_list(sh, link) < 0)
                return (-1);
            if (*link && (*link)->was_expanded)//was_expanded = true, so walk over them
            {
                while (*link && (*link)->was_expanded)
                    link = &(*link)->next;
            }
            else //no split
            {
                link = &curr->next;
            }
        }
        else
        {
            link = &(*link)->next;
        }
    }
    return (0);
}

static int	handle_dollar(t_shell *sh, t_token *t, char *str, t_exp *exp)
{
	if (str[exp->i + 1] == '?')
	{
		handle_error(t, exp, sh);
	}
	else if (is_valid_var_start(str[exp->i + 1]))
	{
		if (handle_var_expansion(sh, t, str, exp) < 0)
			return (-1);
	}
	else
		handle_char(t, str, exp);
	return (0);
}

static int	expand_and_strip(t_shell *sh, t_token *t, int exp_len)
{
	t_exp	exp;
	char	*str;

	t->value = gc_calloc(sh, exp_len + 1, sizeof(char), GC_TEMP);
	t->context = gc_calloc(sh, exp_len + 1, sizeof(char), GC_TEMP);
	if (!t->value || !t->context)
		return (-1);
	str = t->raw;
	init_exp_struct(&exp);
	while (str[exp.i])
	{
		if (str[exp.i] == '\'' || str[exp.i] == '"')
			handle_quote(t, str, &exp);
		else if (!exp.in_sq && str[exp.i] == '$')
		{
			if (handle_dollar(sh, t, str, &exp) < 0)
				return (-1);
		}
		else
			handle_char(t, str, &exp);
	}
	t->value[exp.j] = '\0';
	t->context[exp.j] = '\0';
	return (0);
}
