/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:59:11 by mel               #+#    #+#             */
/*   Updated: 2025/09/27 19:41:49 by mel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ORIGINAL
// int	builtin_echo(t_cmd *cmd)
// {
// 	int i;

// 	if (cmd->argv[1] != NULL && ft_strncmp("-n", cmd->argv[1], 3) != 0)
// 		i = 1;
// 	else
// 		i = 2;
// 	if (cmd->argv[1] != NULL)
// 	{
// 		while (cmd->argv[i] != NULL)
// 		{
// 			ft_putstr_fd(cmd->argv[i], 1);
// 			i++;
// 			if (cmd->argv[i] != NULL)
// 				write(1, " ", 1);
// 		}
// 		if (ft_strncmp("-n", cmd->argv[1], 3) != 0)
// 			ft_putstr_fd("\n", 1);
// 		return (0);
// 	}
// 	ft_putchar_fd('\n', 1);
// 	return (0);
// }

// GPT SUGGESTED CHANGES
static int is_all_n(char *s)
{
    int i;

    if (!s || s[0] != '-')
        return 0;
    i = 1;
    while (s[i])
    {
        if (s[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

int builtin_echo(t_cmd *cmd)
{
    int i = 1;
    int no_newline = 0;

    // Skip all valid -n options
    while (cmd->argv[i] && is_all_n(cmd->argv[i]))
    {
        no_newline = 1;
        i++;
    }

    // Print the rest of the args
    while (cmd->argv[i])
    {
        ft_putstr_fd(cmd->argv[i], 1);
        if (cmd->argv[i + 1])
            write(1, " ", 1);
        i++;
    }

    // Newline unless suppressed
    if (!no_newline)
        write(1, "\n", 1);

    return 0;
}