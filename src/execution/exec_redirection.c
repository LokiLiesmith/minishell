/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:44:44 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/15 03:41:32 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// dup2(oldfd, newfd);
// if newfd was open, closes newfd before copy

// echo meow > test.txt
// echo meow > echo hi = meow hi in file "echo"

// TODO : 
// REDIRECTION LOOPS

// TODO
// happens in parent:
int	redirect(t_cmd *cmd)
{
	int				fd;
	int				dup;
	t_redir_node	*redir_node;
	
	// CHECK RETURN OF OPEN()
	redir_node = cmd->redirs;

	// go through the redir list while redir_node != NULL
	
	dup = 0;
	if (redir_node->r.type == R_IN)
	{
		fd = open(redir_node->r.target, O_RDONLY);
		if (fd < 0)
			return (perror("open() error"), 1);
		dup = dup2(fd, STDIN_FILENO);
	}
	else if (redir_node->r.type == R_OUT)
	{
		fd = open(redir_node->r.target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open() error"), 1);
		dup = dup2(fd, STDOUT_FILENO);
	}
	else if (redir_node->r.type == R_APPEND)
	{
		fd = open(redir_node->r.target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror("open() error"), 1);
		dup = dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	if (dup < 0)
		return (perror("dup2() error"), 1);
	return (0);
}
// echo hello > test.txt >> out.txt


// cmd 1           cmd 2
//   ls  |   grep s	   >    test.txt		= "src" in test.txt

// "ls" = exec child command w/o redirs, but change stdout to pipe (cmd->next != NULL); change next stdin to stdout
// "grep s > test.txt" = read from previous stdout; exec cmd w redirs; change stdout to test.txt