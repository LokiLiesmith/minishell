/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 22:09:41 by mel               #+#    #+#             */
/*   Updated: 2025/09/13 01:22:54 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// #include "../../include/libft/ft_putstr_fd.c"
// #include "../../include/libft/ft_putchar_fd.c"
// #include "../../include/libft/ft_strlen.c"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("getcwd() failed");
		return (1);
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

// int main(void)
// {
// 	int result = builtin_pwd();

// 	if (result == 0)
// 		printf("builtin_pwd executed successfully\n");
// 	else
// 		printf("builtin_pwd encountered an error\n");

// 	return result;
// }
