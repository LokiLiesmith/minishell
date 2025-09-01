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

void out_string(char *str)
{
	// char	*out;
	char	context[200];
	char	result[200];
	char	varname[100];
	char	*code;
	int		last_exit_code = 123; // GET IT FROM MAIN
	int		i = 0;
	int		j = 0;
	int		k = 0;

	bool in_sq;
	bool in_dq;
	in_sq = false;
	in_dq = false;

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
				k = 0;
				while (code[k])
				{
					result[j] = code[k];
					context[j++] = calc_quotes(in_sq, in_dq);
					k++;
				}
				i += 2;
				free(code);
			}
			else if (is_valid_var_start(str[i + 1]))//VARIABLE NAME EXTRACTION
			{
				// get variable name			
				i++;
				k = 0;
				while (str[i] && is_var_char(str[i]))
					varname[k++] = str[i++];
				varname[k] = '\0';
				// set the temp with getenv(VARNAME)

				char *temp = getenv(varname);
				if(!temp)
					temp = "";
				// printf("VARNAME:%s\n", varname);
				// printf("VAR_VALUE:%s\n", temp);

				//copy and add context, move i the len of VAR
				k = 0;
				while (temp[k])
				{
					// printf("TEMP[%d]:%c\n", l, temp[l]);
					result[j] = temp[k++];
					context[j++] = calc_quotes(in_sq, in_dq);
					// i++;
				}
			}
			else // REGULAR ? inside ""
			{
				result[j] = str[i++];
				context[j++] = calc_quotes(in_sq, in_dq);
			}
		}
		else
		{
			context[j] = calc_quotes(in_sq, in_dq);
			// printf("%d, ", context[j]);
			// printf("%c -> i:%d, in_sq: %d, in_dq: %d\n", str[i], i, in_sq, in_dq);
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	context[j] = '\0';
	printf("%s\n", result);
	i = 0;
	while(j > 0)
	{
		printf("%d", context[i++]);
		j--;
	}
	printf("\n");
	printf("strlen(input):%ld\n", ft_strlen(str));
	printf("strlen(output):%ld\n", ft_strlen(result));
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
	out_string(input);
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