/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:58:47 by mel               #+#    #+#             */
/*   Updated: 2025/10/03 22:26:46 by msalangi         ###   ########.fr       */
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

static int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!ft_isdigit(s[i]))
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_shell *sh, t_cmd *cmd)
{
	if (!cmd->argv[1])
		clean_exit(sh);
	if (!is_numeric(cmd->argv[1]))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		sh->last_exit_code = 2;
		clean_exit(sh);
	}
	if (cmd->argv[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		sh->last_exit_code = 1;
		return (1);
	}
	sh->last_exit_code = ft_atoi(cmd->argv[1]) % 256;
	clean_exit(sh);
	return (0);
}
