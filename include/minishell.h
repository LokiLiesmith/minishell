/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:10:12 by mrazem            #+#    #+#             */
/*   Updated: 2025/09/08 19:12:00 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>

//READLINE STUFF
# include <readline/readline.h>
# include <readline/history.h>

//OUR LIBRARIES
# include "../include/libft/libft.h"
# include "../include/get_next_line/get_next_line.h"

////////////////////////////////////////////////////////////////////////////////
//								  MAIN STRUCT / ENUMS						  //
////////////////////////////////////////////////////////////////////////////////

/// Builtin number enum
typedef enum e_builtin
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin;

//Redirection type enum (IN, OUT, APPEND or HEREDOC???)
typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

////////////////////////////////////////////////////////////////////////////////
//								STRUCTS / LINKED LISTS						  //
////////////////////////////////////////////////////////////////////////////////

typedef struct s_redir
{
	t_redir_type		type;		//IN, OUT, APPEND, HEREDOC
	char				*target;	//filepath? destination?
	int					fd;			//0, 1
}	t_redir;

//Redirection LinkedList (bunch of t_redir nodes pointing to the next one)
typedef struct s_redir_node
{
	t_redir				r;
	struct s_redir_node	*next;
}	t_redir_node;

// One command -> pipe to pipe (pipe is a delimiter, kinda. redirects are part of the same command)
typedef struct s_cmd
{
	char				**argv;		//argv[0]...argv[n+1]=NULL, array of strings, here is where the -n flag would also be
	t_redir_node		*redirs;	//list of redirects, NULL = no redirects
	t_builtin			builtin;	//builtin number based on the enum
}	t_cmd;

// Command LinkedList (cmd node pointing to the next one, ends with NULL, thats also when we are done?)
typedef	struct s_cmd_node
{
	t_cmd				cmd;
	struct s_cmd_node	*next;
}	t_cmd_node;

////////////////////////////////////////////////////////////////////////////////
//							TOKENIZER STRUCTS / ENUM						  //
////////////////////////////////////////////////////////////////////////////////

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
	
typedef struct s_lexer //had to implement to save lines
{
	t_token_type	op;
	int				i;
	ssize_t			len;
	t_token			*head;
	t_token			*tail;
}	t_lexer;

////////////////////////////////////////////////////////////////////////////////
//								 EXPANDER									  //
////////////////////////////////////////////////////////////////////////////////
typedef struct s_exp
{
	int		i;
	int		j;
	// int		k;
	int		count;
	bool	in_dq;
	bool	in_sq;
	bool	in_exp;
}	t_exp;

void		expand_tokens(t_token **head, int last_exit_code);
int			expansion_len(char *str, int last_exit_code);

// expansion_utils.c
void		increment_counters(int *i, int *b);
// int			calc_quotes(bool in_sq, bool in_dq);
char			get_context(bool in_sq, bool in_dq, bool in_exp);
void		update_quotes(char c, bool *in_sq, bool *in_dq);
void		init_exp_struct(t_exp *exp);

// var_utils.c
int			get_error_len(int last_exit_code);
int			varname_len(char *str);
char		*extract_varname(char *str, int *i);
bool		is_valid_var_start(char c);
bool		is_var_char(char c);

void 		free_tokens(t_token *token);

////////////////////////////////////////////////////////////////////////////////
//								  LEXER										  //
////////////////////////////////////////////////////////////////////////////////

ssize_t		scan_operator(const char *str, int i, t_token_type *type);
ssize_t		scan_word(const char *str, size_t i);
t_token		*tokenize(char *str, bool *open_quotes);
void		push_token(t_token **head,t_token **tail, t_token_type type, char *start, int len);
int			ft_is_space(int c);
int			ft_is_operator(int c);

////////////////////////////////////////////////////////////////////////////////
//								 BUILT INS 									  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//								  FIELD SPLIT										  //
////////////////////////////////////////////////////////////////////////////////

void	ctx_split_to_list(t_token **t);
void	splice_token_list(t_token **link_to_old, t_token *new_head, t_token* new_tail);
int		ctx_push_token(t_token **h, t_token **tail, t_token *old, int i, int len);
int		fill_ctx_token(t_token *new, int i, int len, t_token *old);
int		ctx_split_len(char *str, char *context, int i);
void 	free_list(t_token *head);
void 	free_token(t_token *t);


#endif
