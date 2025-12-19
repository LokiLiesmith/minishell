/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 01:45:43 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/04 01:45:44 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

/////////////////////////TESTING STUFF//////////////////
void	print_env(t_env *env)
{
	while (env)
	{
		printf("type: %s\n", env->type);
		printf("value: %s\n", env->value);
		env = env->next;
	}
}
///////////////////////////////////////////////////////

static int	calc_new_lvl(int lvl)
{
	if (lvl < 0)
		lvl = 0;
	else if (lvl >= 1000)
		lvl = 1;
	else
		lvl++;
	return (lvl);
}

static void	update_shlvl(t_shell *sh)
{
	char	*lvl_str;
	int		lvl;
	int		new_lvl;

	lvl_str = get_env_value(sh, "SHLVL");
	if (!lvl_str)
	{
		set_env_value(sh, sh->env, "SHLVL", "1");
		return ;
	}
	lvl = ft_atoi(lvl_str);
	new_lvl = calc_new_lvl(lvl);
	lvl_str = ft_itoa(new_lvl);
	if (!lvl_str)
		return ;
	set_env_value(sh, sh->env, "SHLVL", lvl_str);
	free(lvl_str);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;

	(void)ac;
	(void)av;
	ft_bzero(&sh, sizeof(t_shell));
	sh.env = dup_env(&sh, envp);
	update_shlvl(&sh);
	sh.last_exit_code = 0;
	signal_setup();
	shell_loop(&sh);
	gc_free_all(&sh);
	return (0);
}
