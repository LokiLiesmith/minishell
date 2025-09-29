/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:58:47 by mel               #+#    #+#             */
/*   Updated: 2025/09/29 16:55:55 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static void	clean_exit(t_shell *sh)
{
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	gc_free_all(sh);
	exit(sh->last_exit_code);
}

void	builtin_exit(t_shell *sh, t_cmd *cmd)
{
	int	i;
	
	i = 0;
	if (cmd->argv[1] == NULL)
		clean_exit(sh);
	else
	{
		while (cmd->argv[1][i] && ft_isdigit(cmd->argv[1][i]))
			i++;
		if (cmd->argv[1][i] == '\0')
			sh->last_exit_code = ft_atoi(cmd->argv[1]);
		else
		{
			sh->last_exit_code = 255;
			ft_putstr_fd("exit: numeric argument required\n", 2);
			clean_exit(sh);
		}
	}
	clean_exit(sh);
}
