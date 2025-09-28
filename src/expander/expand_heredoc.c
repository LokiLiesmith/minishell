#include "minishell.h"

char   *expand_string(t_shell *sh, char *str)
{
    t_exp	exp;
    int		new_len;
    char	*out;
	char 	*varname;
	char	*temp;

    init_exp_struct(&exp);
    new_len = expansion_len(sh, str);
    out = gc_malloc(sh, new_len + 1, GC_TEMP);
    if (!out)
        return (NULL);
    while (str[exp.i])
	{
		if (str[exp.i] == '$' && is_valid_var_start(str[exp.i + 1]))
		{
			varname = extract_varname(sh, str, exp.i);
			temp = get_env_value(sh, varname);
			if (!temp)
				temp = "";
			
		}
		else if (str[exp.i] == '$' && str[exp.i + 1] == '?')
        {
            temp = ft_itoa(sh->last_exit_code);
            k = 0;
            while (temp[k])
                out[exp.j++] = temp[k++];
            free(temp); //itoa mallocs
            exp.i += 2;
            continue;
        }
	
	}
}

