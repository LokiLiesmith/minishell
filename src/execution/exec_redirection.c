/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:44:44 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/28 17:53:55 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	r_out(t_redir_node *redir_node)
{
	int fd;
	int dup;
	
	fd = -1;
	dup = -1;
	fd = open(redir_node->r.target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open() error"), 1);
	dup = dup2(fd, STDOUT_FILENO);
	if (dup < 0)
		return (perror("dup2() error"), 1);
	close(fd);
	return (0);
}

static int	r_append(t_redir_node *redir_node)
{
	int fd;
	int dup;
	
	fd = -1;
	dup = -1;
	fd = open(redir_node->r.target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror("open() error"), 1);
	dup = dup2(fd, STDOUT_FILENO);
	if (dup < 0)
		return (perror("dup2() error"), 1);
	close(fd);
	return (0);
}

static int	r_in(t_redir_node *redir_node)
{
	int	fd;
	int	dup;

	fd = -1;
	dup = -1;
	fd = open(redir_node->r.target, O_RDONLY);
	if (fd < 0)
		return (perror("open() error"), 1);
	dup = dup2(fd, STDIN_FILENO);
	if (dup < 0)
		return (perror("dup2() error"), 1);
	close(fd);
	return (0);
}
static int	redirect(t_redir_node *redir_node)
{
	if (redir_node && redir_node->r.type == R_IN)
	{
		if (r_in(redir_node))
			return (1);
	}
	else if (redir_node && redir_node->r.type == R_OUT)
	{
		if (r_out(redir_node))
			return (1);
	}
	else if (redir_node && redir_node->r.type == R_APPEND)
	{
		if (r_append(redir_node))
			return (1);
	}
	else
		return (ft_putstr_fd("Uknown redirection\n", 2), 1);
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