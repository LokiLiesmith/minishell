/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 03:15:29 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/04 03:31:24 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
///handle_word_token helper
static int	append_arg_node(t_strlist **arglst, t_strlist *new)
{
	t_strlist	*current;

	if (!*arglst)
		*arglst = new;
	else
	{
		current = *arglst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}

int	handle_word_tkn(t_shell *sh, t_token **t, int *err, t_strlist **arglst)
{
	t_strlist	*new;
	t_token		*token;

	token = *t;
	if (token->value[0] == '\0' && !is_quoted_empty(token))
	{
		*t = token->next;
		return (0);
	}
	new = gc_malloc(sh, sizeof(t_strlist), GC_TEMP);
	if (!new || !token || !token->value)
		return (*err = 1, -1);
	new->str = token->value;
	new->next = NULL;
	append_arg_node(arglst, new);
	*t = token->next;
	return (0);
}

typedef struct s_parse_ctx
{
	t_shell		*sh;
	t_token		**tokens;
	t_cmd		*cmd;
	int			*err;
	t_strlist	**arglst;
}	t_parse_ctx;

static int	dispatch_token(t_parse_ctx *ctx)
{
	if ((*(ctx->tokens))->type == WORD)
	{
		if (handle_word_tkn(ctx->sh, ctx->tokens, ctx->err, ctx->arglst) < 0)
			return (-1);
	}
	else if (is_redir_token((*(ctx->tokens))->type))
	{
		if (handle_redir_token(ctx->sh, ctx->tokens, ctx->cmd, ctx->err) < 0)
			return (-1);
	}
	else
	{
		report_parse_error(*(ctx->tokens), ctx->err);
		return (-1);
	}
	return (0);
}

t_token	*parse_command(t_shell *sh, t_token *tokens, t_cmd *cmd, int *err)
{
	t_strlist	*arglst;
	t_parse_ctx	ctx;

	arglst = NULL;
	*err = 0;
	if (!tokens)
		return (NULL);
	if (tokens->type == PIPE)
		return (report_parse_error(tokens, err));
	ctx.sh = sh;
	ctx.tokens = &tokens;
	ctx.cmd = cmd;
	ctx.err = err;
	ctx.arglst = &arglst;
	while (tokens && tokens->type != PIPE)
	{
		if (dispatch_token(&ctx) < 0)
			return (NULL);
	}
	cmd->argv = convert_arglst(sh, arglst);
	set_builtin(cmd);
	return (tokens);
}
