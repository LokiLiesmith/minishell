#include "minishell.h"

int	get_error_len(int last_exit_code)
{
	char	*code;
	int		len;
	
	code = ft_itoa(last_exit_code);
	if (!code)
		return (0);
	len = ft_strlen(code);
	free(code);
	return (len);
}

int	varname_len(char *str)
{
	int	k;

	k = 0;
	while (*str && is_var_char(*str))
	{
		str++;
		k++;
	}
	return (k);
}

char	*extract_varname(char *str, int *i)
{
	char	*varname;
	int		len;
	int		k;
	int		j;

	k = 0;
	j = *i;
	len = varname_len(str + *i);
	varname = malloc(sizeof(char) * len + 1);

	if (!varname)
		return (NULL);
	while (str[j] && is_var_char(str[j]))
		varname[k++] = str[j++];
	varname[k] = '\0';
	*i = j;
	// printf("%s\n", varname);
	return(varname);
}

bool	is_valid_var_start(char c)
{
	return ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c == '_'));
}

bool is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			(c == '_'));
}