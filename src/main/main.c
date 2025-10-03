#include "minishell.h"

// int signal;

volatile sig_atomic_t g_exit_status = 0;

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

static t_env	*dup_env(t_shell *sh, char **envp)
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

static int	calc_new_lvl(int lvl)
{
	if (lvl < 0)
		lvl = 0;
	else if(lvl >= 1000)
		lvl = 1;
	else
		lvl++;
	return lvl; 
}

static void	update_shlvl(t_shell *sh)
{
	char	*lvl_str;
	int		lvl;
	int		new_lvl;

	lvl_str = get_env_value(sh, "SHLVL");
	if(!lvl_str)
	{
		set_env_value(sh, sh->env, "SHLVL", "1");
		return ;
	}
	lvl = ft_atoi(lvl_str);
	new_lvl = calc_new_lvl(lvl);
	lvl_str = ft_itoa(new_lvl);
	if(!lvl_str)
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
