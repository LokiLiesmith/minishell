#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int c);

int calc_quotes(bool in_sq, bool in_dq)
{
	if (in_dq)
		return (2);
	else if (in_sq)
		return (1);
	return (0);
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
void update_quotes(char c, bool *in_sq, bool *in_dq)
{
	if (!*in_dq && c == '\'')
		*in_sq = !*in_sq;
	else if (!*in_sq && c == '"')
		*in_dq = !*in_dq;
}

void increment_counters(int *i, int *b)
{
	(*i)++;
	(*b)++;
}
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

typedef struct s_exp
{
	int		i;
	int		count;
	bool	in_dq;
	bool	in_sq;
}	t_exp;

void	init_exp_struct(t_exp *exp)
{
	exp->i = 0;
	exp->count = 0;
	exp->in_sq = false;
	exp->in_dq = false;
}

static void handle_quote(const char *str, t_exp *exp)
{
	update_quotes(str[exp->i], &exp->in_sq, &exp->in_dq);
	exp->i++;
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

int	main(void)
{
	// char *input = "Mark \'singles\' \"doubles\" \'s_exp: $USER\' \"d_exp: $USER\" \'s_err: $?\' \"d_err: $?\" \"just a ?\"";
	char *input = "\'$USER\' \"$USER\" $HOME $? \"$?\" \'$?\'";
	// char *input = "$HOME";
	
	printf("%s\n", input);
	printf("%s\n", getenv("HOME"));
	printf("expanded input len[%d]\n", expansion_len(input, 144));
	// out_string(input, 144);
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;

	copy = (char *)malloc(ft_strlen(s) +1);
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	int_len(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count++;
		nbr = -nbr;
	}
	if (nbr == 0)
		count++;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int c)
{
	long	nbr;
	int		len;
	char	*result;

	nbr = c;
	len = int_len(nbr);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		result[0] = '0';
	while (nbr > 0)
	{
		result[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (result);
}


// Run these through your stripper and then through expansion when you add it:
// Quotes & adjacency
// echo a"b"c → arg: abc
// echo "a"b'c' → arg: abc
// echo "" → one empty arg
// echo '' → one empty arg

// Backslash
// echo "a\"b" → a"b (POSIX-y)
// echo "a\qb" → POSIX-y: backslash preserved → a\qb

// Variables
// echo $USER"x" → username followed by x
// echo "$USER"x → same
// echo '$USER' → $USER
// echo "$EMPTY"x with EMPTY unset → x (note: becomes x, still one arg)

// Redirections (after expansion; check “ambiguous redirect”)
// > "$EMPTY" → filename becomes empty → error
// > $FOO where FOO="a b" (unquoted) → splits to 2 words → ambiguous redirect

// Here-doc delimiters
// <<EOF expands vars in body
// <<'EOF' does no expansion