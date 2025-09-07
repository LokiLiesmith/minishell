/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:59:11 by mel               #+#    #+#             */
/*   Updated: 2025/09/06 23:47:00 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_echo(t_cmd *cmd)
{
	int i;

	if (ft_strncmp("-n", cmd->argv[1], 3) != 0)
		i = 1;
	else
		i = 2;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		write(1, ' ', 1);
		i++;
	}
	// if no -n, write newline
	if (ft_strncmp("-n", cmd->argv[1], 3) != 0)
		write(cmd->redirs->r.fd, "\n", 1);
}

// echo hi
// echo hi >> test

// 