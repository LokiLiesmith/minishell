/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:44:44 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/27 10:33:09 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redirect(t_redir_node *redir_node)
{
	int		fd;
	int		dup;
	
	dup = 0;
	if (redir_node && redir_node->r.type == R_IN)
	{
		fd = open(redir_node->r.target, O_RDONLY);
		if (fd < 0)
			return (perror("open() error"), 1);
		dup = dup2(fd, STDIN_FILENO);
	}
	else if (redir_node && redir_node->r.type == R_OUT)
	{
		fd = open(redir_node->r.target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open() error"), 1);
		dup = dup2(fd, STDOUT_FILENO);
	}
	else if (redir_node && redir_node->r.type == R_APPEND)
	{
		fd = open(redir_node->r.target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror("open() error"), 1);
		dup = dup2(fd, STDOUT_FILENO);
	}
	else
		return (ft_putstr_fd("Uknown redirection\n", 2), 1);
	close(fd);
	if (dup < 0)
		return (perror("dup2() error"), 1);
	return (0);
}


int	handle_redirections(t_cmd *cmd)
{
	t_redir_node *current;

	current = cmd->redirs;
	while (current)
	{
		if (redirect(current))
			return (1);
		current = current->next;
	}
	return (0);
}

// cmd 1           cmd 2
//   ls  |   grep s	   >    test.txt		= "src" in test.txt

// "ls" = exec child command w/o redirs, but change stdout to pipe (cmd->next != NULL); change next stdin to stdout
// "grep s > test.txt" = read from previous stdout; exec cmd w redirs; change stdout to test.txt