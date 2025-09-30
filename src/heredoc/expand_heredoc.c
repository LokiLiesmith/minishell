#include "minishell.h"

static int	handle_var_expansion_len(t_shell *sh, char *str, t_exp *exp)
{
	char	*varname;
	char	*temp;
	int		var_len;

	exp->i++;
	varname = extract_varname(sh, str, &exp->i);
	if (!varname)
		return (-1);
	temp = get_env_value(sh, varname); // TODO: needs to read from env LList not from actual env
	if (!temp)
		temp = "";
	var_len = ft_strlen(temp);
    // printf("[DEBUG]Var_len:%d\n", var_len);
    // printf("[DEBUG]Var_name:%s\n", varname);
	exp->count += var_len;
    // printf("[DEBUG]exp->count:%d\n", exp->count);
	return (0);
}

static int	handle_dollar_len(t_shell *sh, char *str, t_exp *exp)
{
	if (str[exp->i + 1] == '?')
	{
		exp->count += get_error_len(sh->last_exit_code);
		exp->i += 2;
		return (0);
	}
	else if (is_valid_var_start(str[exp->i + 1]))
		return (handle_var_expansion_len(sh, str, exp));
	// Only count the '$' as a literal char; leave next char for next loop
	exp->i++;
	exp->count++;
	return (0);
}

static int	heredoc_len(t_shell *sh, char *str)
{
	t_exp	exp;

	init_exp_struct(&exp);
	while (str[exp.i])
	{
		if (str[exp.i] == '$')
		{
			if (handle_dollar_len(sh, str, &exp) < 0)
				return (-1);
		}
		else
			increment_counters(&exp.i, &exp.count);
	}
	return (exp.count);
}

char *expand_heredoc(t_shell *sh, t_redir *r, char *line)
{
    char    *expanded;

    if (!line)
        return (NULL);
    if (r->heredoc_quoted)
        expanded = gc_strdup(sh, line, GC_TEMP);
    else
        expanded = expand_string(sh, line);
    free(line);
    return (expanded);

}

char *expand_string(t_shell *sh, char *str)
{
    t_exp   exp;
    int     new_len;
    char    *out;
    char    *varname;
    char    *value;

    if (!str)
        return (NULL);

    init_exp_struct(&exp);
    new_len = heredoc_len(sh, str);
    out = gc_malloc(sh, new_len + 1, GC_TEMP);
    while (str[exp.i])
    {
        if (str[exp.i] == '$' && str[exp.i + 1] == '?')
        {
            exp.j += write_exit_code(out + exp.j, sh->last_exit_code);
            exp.i += 2;
        }
        else if (str[exp.i] == '$' && is_valid_var_start(str[exp.i + 1]))
        {
            exp.i++;
            varname = extract_varname(sh, str, &exp.i);
            value = get_env_value(sh, varname);
            if (!value)
                value = "";
            while (*value)
            {
                out[exp.j++] = *value++;
                // printf("[DEBUG] i=%d j=%d c='%c'\n", exp.i, exp.j, str[exp.i]);
            }
            continue;
        }
        else
            out[exp.j++] = str[exp.i++];
    }
    out[exp.j] = '\0';
    return (out);
}
