#include "minishell.h"

int g_signal;

/////////////////////////TESTING STUFF//////////////////
void	print_env(t_env *env)
{
	while (env)
	{
		printf("var_name: %s\n", env->var_name);
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
			new->var_name = gc_substr_global(sh, envp[i], 0, eq_pos - envp[i]);
			new->value = gc_strdup(sh, eq_pos + 1, GC_GLOBAL);
			new->next = head;
			head = new;
		}
		i++;
	}
	return (head);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	sh;

	(void)ac;
	(void)av;

	ft_bzero(&sh, sizeof(t_shell));

	sh.env = dup_env(&sh, envp);
	sh.last_exit_code = 0;

	// print_env(sh.env);
	signal_setup();
	shell_loop(&sh);	//TODO:
	// free_env(sh.env);
	gc_free_all(&sh);
	return (0);
}
