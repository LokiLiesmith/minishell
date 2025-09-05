#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
typedef enum e_token_type
{
	WORD,
	PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*raw;
	char			*value;
	char			*context;
	struct s_token	*next;
}	t_token;
///////////////////////////////////////////////////////////////////////////////
								// SETUP //

void	init_token(t_token *t, char *raw, char *value, char *context)
{
	t->raw = strdup(raw);
	t->value = strdup(value);
	t->context = strdup(context);
}
void 	free_token(t_token *t)
{
	free(t->raw);
	free(t->value);
	free(t->context);
}

void print_token(t_token *t)
{
	printf("raw: %s\n", t->raw);
    printf("val: %s\n", t->value);
    printf("ctx: %s\n", t->context);
}
//////////////////////////////////////////////////////////////////////////////////////

static int ft_is_delim(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void ctx_split(t_token *t)
{
	int	i;
	int len;

	i = 0;
	len = 0;
	while(t->value[i])
	{
		
		if (!ft_is_delim(t->value[i]))
			len++;
		//measure til delimiter (' ', '\n', '\t')
		// write(1, &t->value[i], 1);
		i++;
		printf("%d\n", len);
	}
	// write(1, "\n", 1);
}
// aaa b b b
// aaa





int	main(void)
{
	char	*raw = "\"$VAR\""; // VAR="aaa b b b"
	// char	*value = "aaa b b b";
	// char	*context = "eee0eeeee";
	char	*value = "aaa\nb\n\nbb";
	char	*context = "eee0e00ee";
    t_token	token;

	init_token(&token, raw, value, context);
	print_token(&token);
    ctx_split(&token);
	// print_token(&token);
	free_token(&token);
    
	return (0);
}