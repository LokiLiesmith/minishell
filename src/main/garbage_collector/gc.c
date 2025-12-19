/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 01:46:31 by msalangi          #+#    #+#             */
/*   Updated: 2025/10/04 01:49:04 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*gc_substr_temp(t_shell *sh, const char *s, int start, int len)
{
	int		s_len;
	char	*p;
	t_scope	scope;

	scope = GC_TEMP;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		p = gc_malloc(sh, 1, scope);
		if (!p)
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	if (len > s_len - start)
		len = s_len - start;
	p = gc_malloc(sh, len + 1, scope);
	if (!p)
		return (NULL);
	ft_memcpy(p, s + start, len);
	p[len] = '\0';
	return (p);
}

char	*gc_substr_global(t_shell *sh, const char *s, int start, int len)
{
	int		s_len;
	char	*p;
	t_scope	scope;

	scope = GC_GLOBAL;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		p = gc_malloc(sh, 1, scope);
		if (!p)
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	if (len > s_len - start)
		len = s_len - start;
	p = gc_malloc(sh, len + 1, scope);
	if (!p)
		return (NULL);
	ft_memcpy(p, s + start, len);
	p[len] = '\0';
	return (p);
}

void	*gc_calloc(t_shell *sh, size_t count, size_t size, t_scope scope)
{
	size_t	total;
	void	*ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	total = count * size;
	ptr = gc_malloc(sh, total, scope);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_shell	sh;

// 	sh.env = dup_env(envp);
// 	sh.last_exit_code = 0;

// 	signal_setup();
// 	shell_loop(&sh);

// 	return (0);
// }
