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

static bool is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			(c == '_'));
}

int	ft_measure_varname(char *str)
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
	len = ft_measure_varname(str + *i);
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

void out_string(char *str, int last_exit_code)
{
	// char	*out;
	int		i;
	int		count;
	char	*code;

	int k = 0;
	// int j = 0;
		i = 0;
	// char	context[200];
	// char	result[200];
	char	*varname;

	bool in_sq;
	bool in_dq;
	in_sq = false;
	in_dq = false;

	count = 0;
	while (str[i])
	{
		if (!in_dq && str[i] == '\'')
		{
			in_sq = !in_sq;
			i++;
		}
		else if	(!in_sq && str[i] == '"')
		{
			in_dq = !in_dq;
			i++;
		}
		else if (!in_sq && str[i] == '$') //EXPANSION
		{
			if (str[i + 1] == '?')//ERROR CODE
			{
				code = ft_itoa(last_exit_code);
				if (!code)
					return ;
				count += ft_strlen(code);
				// printf("at error code: Count[%d]\n", count);
				i += 2;
				free(code);
			}
			else if (is_valid_var_start(str[i + 1]))//VARIABLE NAME EXXTRACTION
			{
				i++;
				varname = extract_varname(str, &i);
				char *temp = getenv(varname);
				if(!temp)
					temp = "";
				//copy and add context, move i the len of VAR
				k = 0;
				while (temp[k])
				{
					count++;
					k++;
				}
			}
			else // REGULAR ? inside ""
			{
				count++;
				i++;
				// result[j] = str[i++];
				// context[j++] = calc_quotes(in_sq, in_dq);
			}
		}
		else
		{
			// result[j++] = str[i++];
			i++;
			count++;
		}
	}
	// result[j] = '\0';
	count++;
	// printf("%s\n", result);
	printf("strlen(input):%ld\n", ft_strlen(str));
	printf("expanded count:%d\n", count);
}

// void append_cls()
// {
// 	int i = 0;
// 	if []
// 	cls_stri
// }

int	main(void)
{
	char *input = "Mark \'singles\' \"doubles\" \'s_exp: $USER\' \"d_exp: $USER\" \'s_err: $?\' \"d_err: $?\" \"just a ?\"";
	// char *input = "\'$USER\' \"$USER\" $HOME $? \"$?\" \'$?\'";
	
	printf("%s\n", input);
	out_string(input, 144);
	return (0);
}





















// int	main(int ac, char **av)
// {
// 	char *value;
// 	int last_exit_code;

// 	(void)last_exit_code;
// 	(void)ac;
	
// 	value = ft_strdup(av[1]);
// 	last_exit_code = 0;
// 	printf("input: %s\n", value);
// 	// value = expand_and_remove_quotes(value);
// 	printf("Stripped: %s\n", value);

	

// 	free(value);
// 	return (0);
// }

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