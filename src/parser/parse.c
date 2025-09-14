#include "minishell.h"

void init_cmd_node(t_cmd_node *p)
{
	
}

t_cmd_node	*parse(t_token *tokens, t_shell *sh)
{
	t_cmd_node	*pipeline;

	init_cmd_node(&pipeline);
	while (tokens)
	{
		if (tokens->type == WORD)
			handle_word_token();
		else if (tokens->type == PIPE)
			handle_pipe_token();
		else if (tokens->type == T_IN)
			handle_in_token();
		else if (tokens->type == T_OUT)
			handle_out_token();
		else if (tokens->type == T_APPEND)
			handle_append_token();
		else if (tokens->type == T_HEREDOC)
			handle_heredoc_token();
		tokens = tokens->next;
	}
	return (NULL);
}

void	print_syntax_error(const char *unexpected)
{
	if (!unexpected || *unexpected == '\0')
		fprintf(stderr, "syntax error: unexpected token near 'newline'\n");
	else
		fprintf(stderr, "syntax error: near unexpected token %s\n", unexpected);
}
