/* // // Input                                  → Stripped
// // --------------------------------------   -----------------------------
// // "abc"                                     abc
// // 'abc'                                     abc
// // \"a\"b                                    "ab
// // '\"double\'\\\\'                           \"double\'\\\\
// // "single"'\"double\'\\\\'                   single\"double\'\\\
// // \ a\ b\ c                                  " a b c"
// // "\\$x"                                     \$x
// // "\$x"                                      $x
// // "foo\qbar"                                 foo\qbar    (q not special)
// // 'back\slash'                               back\slash  (\ literal in single quotes)
// // \                                          \           (trailing backslash unquoted)
// // "unfinished                               error (unclosed) */
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);

char *expand_and_remove_quotes(char * value)
{
	int i;
	int j;
	bool single_q;
	bool double_q;
	char *result;

	result = malloc(strlen(value));
	i = 0;
	j = 0;
	single_q = false;
	double_q = false;

	while (value[i])
	{
		if (value[i] == '\\' && value[i - 1] != '\\')
			i++;
		else if (value[i] == '\'' && !double_q && (i == 0 || value[i - 1] != '\\'))
		{
			// if ()
			single_q = !single_q;
			i++;
		}
		else if (value[i] == '"' && !single_q && (i == 0 || value[i - 1] != '\\'))
		{
			double_q = !double_q;
			i++;
		}
		else
			result[j++] = value[i++];
		
	}
	result[j] = '\0';
	return (result);
}





int	main(int ac, char **av)
{
	char *value;
	int last_exit_code;

	(void)last_exit_code;
	(void)ac;
	
	value = ft_strdup(av[1]);
	last_exit_code = 0;
	printf("input: %s\n", value);
	value = expand_and_remove_quotes(value);
	printf("Stripped: %s\n", value);

	

	free(value);
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