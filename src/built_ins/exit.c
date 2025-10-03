/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 20:58:47 by mel               #+#    #+#             */
/*   Updated: 2025/09/30 19:19:07 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ORIGINAL
// static void	clean_exit(t_shell *sh)
// {
// 	if (isatty(STDIN_FILENO))
// 		write(1, "exit\n", 5);
// 	gc_free_all(sh);
// 	exit(sh->last_exit_code);
// }

// void	builtin_exit(t_shell *sh, t_cmd *cmd)
// {
// 	int	i;
	
// 	i = 0;
// 	if (cmd->argv[1] == NULL)
// 		clean_exit(sh);
// 	else
// 	{
// 		while (cmd->argv[1][i] && ft_isdigit(cmd->argv[1][i]))
// 			i++;
// 		if (cmd->argv[1][i] == '\0')
// 			sh->last_exit_code = ft_atoi(cmd->argv[1]);
// 		else
// 		{
// 			sh->last_exit_code = 2; // 255 for mac
// 			ft_putstr_fd("exit: numeric argument required\n", 2);
// 			clean_exit(sh);
// 		}
// 	}
// 	clean_exit(sh);
// }

// GPT SUGGESTED CHANGES - added multiple arg support (exit 1 2)
#include "../../include/minishell.h"

static void	clean_exit(t_shell *sh)
{
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	gc_free_all(sh);
	exit(sh->last_exit_code);
}

static int	is_numeric(const char *s)
{
	int i = 0;

	if (!s || !*s)
		return (0);
	if (s[i] == '+' || s[i] == '-') // allow sign
		i++;
	if (!ft_isdigit(s[i])) // must have at least one digit
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
	if (!cmd->argv[1]) // no args
		clean_exit(sh);

	if (!is_numeric(cmd->argv[1])) // non-numeric
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		sh->last_exit_code = 2;
		clean_exit(sh);
	}

	if (cmd->argv[2]) // too many args
	{
		ft_putstr_fd("exit\n", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		sh->last_exit_code = 1;
		return (1); // don't exit, just set status
	}

	// valid single numeric
	sh->last_exit_code = ft_atoi(cmd->argv[1]) % 256;
	clean_exit(sh);
	return (0);
}