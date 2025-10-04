/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 01:39:52 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/04 01:48:51 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*dup_env(t_shell *sh, char **envp)
{
	int		i;
	t_env	*head;
	t_env	*new;
	char	*eq_pos;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			new = gc_malloc(sh, sizeof(t_env), GC_GLOBAL);
			new->type = gc_substr_global(sh, envp[i], 0, eq_pos - envp[i]);
			new->value = gc_strdup(sh, eq_pos + 1, GC_GLOBAL);
			new->next = head;
			head = new;
		}
		i++;
	}
	return (head);
}

void	handle_exit(t_shell *sh)
{
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	gc_free_all(sh);
	exit(sh->last_exit_code);
}

int	is_only_spaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_is_space((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}
