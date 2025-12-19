/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:44:44 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/03 22:29:09 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	r_out(t_redir_node *redir_node)
{
	int	fd;
	int	dup;

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
	int	fd;
	int	dup;

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

static int	r_heredoc(t_redir_node *redir_node)
{
	int	dup;

	dup = -1;
	dup = dup2(redir_node->r.fd, STDIN_FILENO);
	if (dup < 0)
		return (perror("dup2() error"), 1);
	close(redir_node->r.fd);
	return (0);
}

int	redirect(t_redir_node *redir_node)
{
	if (redir_node && redir_node->r.type == R_IN && redir_node->r.fd == -1)
	{
		if (r_in(redir_node))
			return (1);
	}
	else if (redir_node && redir_node->r.type == R_IN && redir_node->r.fd != -1)
	{
		if (r_heredoc(redir_node))
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
		return (ft_putstr_fd("uknown redirection\n", 2), 1);
	return (0);
}
