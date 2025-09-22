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

void	*gc_malloc(size_t size, t_scope scope);
char	*gc_strdup(const char *s, t_scope scope);
void	gc_add(void *ptr, t_scope scope);
void	gc_free_scope(t_scope scope);
void	gc_free_all();


