/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:10:12 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/10 18:32:56 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include "../include/libft/libft.h"
# include "../include/get_next_line/get_next_line.h"


/// 						Main struct idea:
////////////////////////////////////////////////////////////////////////////////
//								  ENUMS										  //
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
//								HANDOFF EXAMPLES							  //
////////////////////////////////////////////////////////////////////////////////

// // case for ---> echo -n "oh, hi mark"
// _________________________________________________
// |	1st_cmd										|
// |												|
// |	argv -> ["echo", "-n", "oh, hi mark", NULL]	|
// |	redirs -> NULL								|
// |	builtin = ECHO 								|
// |________________________________________________|
// 		|
// 		V
// _________________________________________________
// |	NULL										|
// |												|
// |												|
// |												|
// |				 								|
// |_______________________________________________|

	
// // case for ---> echo -n "oh, hi mark" > out.txt < | grep hi >> log.txt
//				 	^			1st_cmd			   ^  ^		2nd_cmd	   ^

// _________________________________________________
// |	1st_cmd										|
// |												|
// |	argv -> ["echo", "-n", "oh, hi mark", NULL]	|
// |	redirs -> [R_OUT, "out.txxt", 1] -> NULL	|
// |	builtin = ECHO 								|
// |_______________________________________________|
// 		|
// 		V													here's how the redirection list looks	
// _________________________________________________		_____________________________________	________________________________
// |	2nd_cmd										|		|	t_redir_node					|	|	t_redir_node 2				|
// |												|		|	type = R_APPEND					|	|	type = R_OUT				|
// |	argv -> ["grep", "hi", NULL]				|		|	target = "log.txt"				|	|	target = "  asdas"			|
// |	redirs -> [R_APPEND, "log.txt", 1] -> NULL	|		|	fd = 1							|-->|	fd = 0;						|
// |	builtin = NONE 								|		|	next --------> *t_redirnode 2	|	|	next ---> NULL				|
// |_______________________________________________|		|___________________________________|	|_______________________________|
// 		|
// 		V
// 		NULL


////////////////////////////////////////////////////////////////////////////////
//								  PARSER									  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//								  LEXER										  //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//								 BUILT INS 									  //
////////////////////////////////////////////////////////////////////////////////

#endif
