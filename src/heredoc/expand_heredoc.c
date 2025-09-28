#include "minishell.h"

char *expand_heredoc(t_shell *sh, t_redir *r, char *line)
{
    char    *expanded;
    if (!line)
        return (NULL);
    if (r->heredoc_quoted)
        return (line);
    else
    {
        expanded = expand_string(sh, line);
        free(line);
        return (expanded);
    }
}

char	*expand_string(t_shell *sh, char *str)
{
    t_exp	exp;
    int		new_len;
    char	*out;
    char	*varname;
    char	*value;

	if (!str)
		return (NULL);

    init_exp_struct(&exp);

	new_len = expansion_len(sh, str);
	out = gc_malloc(sh, new_len + 1, GC_TEMP);
    if (!out)
		return (NULL);
    while (str[exp.i])
    {
        if (str[exp.i] == '$' && str[exp.i + 1] == '?')
        {
			exp.j += write_exit_code(out + exp.j, sh->last_exit_code);
			exp.i += 2;
        }
        else if (str[exp.i] == '$' && is_valid_var_start(str[exp.i + 1]))
        {
            varname = extract_varname(sh, str, &exp.i);
            value = get_env_value(sh, varname);
            if (!value)
                value = "";
            while (*value)
                out[exp.j++] = *value++;
        }
        else
        {
            out[exp.j++] = str[exp.i++];
        }
    }
    out[exp.j] = '\0';
    return (out);
}

