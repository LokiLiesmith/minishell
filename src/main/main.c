#include "minishell.h"

int g_signal;

/////////////////////////TESTING STUFF//////////////////
static void print_env(t_env *env)
{
	while(env)
	{
		printf("var_name: %s\n", env->var_name);
		printf("value: %s\n", env->value);
		env = env->next;
	}
}

///////////////////////////////////////////////////////






static void free_env(t_env *env)
{
	t_env	*temp;

	while(env)
	{
		temp = env->next;
		free(env->var_name);
		free(env->value);
		free(env);
		env = temp;
	}
}

static t_env *dup_env(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*new;
	char	*eq_position;

	head = NULL;
	i = 0;
	while(envp[i])
	{
		eq_position = ft_strchr(envp[i], '=');
		if (eq_position)
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return (NULL);
			new->var_name = ft_substr(envp[i], 0, eq_position - envp[i]);
			new->value = ft_strdup(eq_position + 1);
			new->next = head;
			head = new;
		}
		i++;
	}
	return (head);
}

int main(int ac, char **av, char **envp)
{

	t_shell	sh;

	(void)ac;
	(void)av;

	sh.env = dup_env(envp);
	sh.last_exit_code = 0;

	print_env(sh.env);
	signal_setup();
	shell_loop(&sh);	//TODO:
	free_env(sh.env);
	return (0);
}