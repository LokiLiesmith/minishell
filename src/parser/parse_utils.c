/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 02:07:50 by mrazem            #+#    #+#             */
/*   Updated: 2025/10/04 03:21:33 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_arglst(t_shell *sh, t_strlist *list)
{
	t_strlist	*tmp;
	char		**argv;
	int			i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	argv = gc_malloc(sh, (sizeof(char *) * (i + 1)), GC_TEMP);
	if (!argv)
		return (NULL);
	i = 0;
	while (list)
	{
		argv[i] = list->str;
		i++;
		list = list->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	is_redir_token(t_token_type type)
{
	return (type == T_IN || type == T_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

// strcmp = 0, if match found.
t_builtin	get_builtin_type(char *s)
{
	if (!s)
		return (NONE);
	if (!ft_strcmp(s, "echo"))
		return (ECHO);
	if (!ft_strcmp(s, "cd"))
		return (CD);
	if (!ft_strcmp(s, "pwd"))
		return (PWD);
	if (!ft_strcmp(s, "export"))
		return (EXPORT);
	if (!ft_strcmp(s, "unset"))
		return (UNSET);
	if (!ft_strcmp(s, "env"))
		return (ENV);
	if (!ft_strcmp(s, "exit"))
		return (EXIT);
	return (NONE);
}

void	set_builtin(t_cmd *cmd)
{
	char	*first;

	first = NULL;
	if (cmd->argv)
		first = cmd->argv[0];
	cmd->builtin = get_builtin_type(first);
}
