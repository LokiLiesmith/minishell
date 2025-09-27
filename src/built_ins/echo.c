/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:59:11 by mel               #+#    #+#             */
/*   Updated: 2025/09/27 08:22:29 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_echo(t_cmd *cmd)
{
	int i;

	if (ft_strncmp("-n", cmd->argv[1], 3) != 0)
		i = 1;
	else
		i = 2;
	while (cmd->argv[i] != NULL)
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (ft_strncmp("-n", cmd->argv[1], 3) != 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
