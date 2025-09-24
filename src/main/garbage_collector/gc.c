#include "minishell.h"

//exit on fatal error, allocation failed --> no sh struct
void	gc_fatal(void)
{
	write(STDERR_FILENO, "fatal error\n", 12);
	exit(EXIT_FAILURE);
}

t_gc	*gc_newnode(void *ptr, t_scope scope)
{
	t_gc	*node;

	node = malloc(sizeof(t_gc));
	if (!node)
		gc_fatal();
	node->ptr = ptr;
	node->scope = scope;
	node->next = NULL;
	return (node);
}

void	*gc_malloc(t_shell *sh, size_t size, t_scope scope)
{
	void	*ptr;

	if (!sh)
		gc_fatal();
	if (size == 0)
		size = 1;
	ptr = malloc(size);
	if (!ptr)
		gc_fatal();
	gc_add(sh, ptr, scope);
	return (ptr);
}

char	*gc_strdup(t_shell *sh, const char *s, t_scope scope)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = gc_malloc(sh, len, scope);
	ft_memcpy(dup, s, len);
	return (dup);
}


int	main(int ac, char **av, char **envp)
{
	t_shell	sh;

	sh.env = dup_env(envp);
	sh.last_exit_code = 0;

	signal_setup();
	shell_loop(&sh);

	return (0);
}

