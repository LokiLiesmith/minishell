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

int	main(void)
{
	char	*raw = "\"$VAR\""; // VAR="aaa b b b"
	char	*value = "aaa b b b";
	char	*context = "eee0eeeee";
    t_token	token;

	init_token(&token, raw, value, context);
	printf("raw %s\n", token.raw);
    printf("val: %s\n", token.value);
    printf("ctx: %s\n", token.context);
    // ctx_split(token);
	free_token(&token);
    
	return (0);
}