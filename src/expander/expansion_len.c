#include "minishell.h"

static void handle_quote(const char *str, t_exp *exp);
static int	handle_dollar(char *str, t_exp *exp, int last_exit);
static int	handle_var_expansion(char *str, t_exp *exp);

int	expansion_len(char *str, int last_exit_code)
{
	t_exp	exp;
	
	init_exp_struct(&exp);
	while (str[exp.i])
	{
		if (str[exp.i] == '\'' || str[exp.i] == '"')
			handle_quote(str, &exp);
		else if(!exp.in_sq && str[exp.i] == '$')
		{
			if (handle_dollar(str, &exp, last_exit_code) < 0)
				return (-1);
		}
		else
			increment_counters(&exp.i, &exp.count);
	}
	return (exp.count);
}
static void handle_quote(const char *str, t_exp *exp)
{
	update_quotes(str[exp->i], &exp->in_sq, &exp->in_dq);
	exp->i++;
}

static int	handle_dollar(char *str, t_exp *exp, int last_exit)
{
	if (str[exp->i + 1] == '?')
	{
		exp->count += get_error_len(last_exit);
		exp->i += 2;
		return (0);
	}
	else if (is_valid_var_start(str[exp->i + 1]))
		return (handle_var_expansion(str, exp));
	increment_counters(&exp->i, &exp->count);
	return (0);
}

static int	handle_var_expansion(char *str, t_exp *exp)
{
	char	*varname;
	char	*temp;
	int		var_len;

	exp->i++;
	varname = extract_varname(str, &exp->i);
	if (!varname)
		return (-1);
	temp = getenv(varname);
	if (!temp)
		temp = "";
	var_len = ft_strlen(temp);
	free(varname);
	exp->count += var_len;
	return (0); 
}

