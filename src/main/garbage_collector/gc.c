#include "minishell.h"

typedef enum e_scope
{
	GC_TEMP,
	GC_GLOBAL
}	t_scope;

typedef	struct s_gc
{
	void		*ptr;
	t_scope		scope;
	struct s_gc	*next;
}	t_gc;

void	*gc_malloc(t_shell *sh, size_t size, t_scope scope);
char	*gc_strdup(const char *s, t_scope scope);
void	gc_add(void *ptr, t_scope scope);
void	gc_free_scope(t_scope scope);
void	gc_free_all();


void *gc_malloc(t_shell *sh, size_t size, t_scope scope)
{
	void	*ptr;
	t_gc	*node;

	ptr = malloc(size);
	if (!ptr)
		return(NULL);
	node = malloc(sizeof(t_gc));
	if(!node)
	{
		free (ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->scope = scope;
	node->next = sh->gc;

}

int	main (int ac, char **av, char **envp)
{
	t_shell sh;
	sh.env = dup_env(envp);
	sh.last_exit_code = 0;
	
	signal_setup();
	shell_loop(&sh);

	return (0);
}
