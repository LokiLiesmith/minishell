/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazem <mrazem@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:54:43 by mrazem            #+#    #+#             */
/*   Updated: 2025/08/10 19:39:25 by mrazem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// static void	init_test_struct(t_cmd_node *pipeline)
// {

// 	char *argv = malloc(sizeof (char *) * 3);
// 	pipeline->cmd->argv = &argv;

// }

int	main(void)
{
	t_cmd_node	pipeline;

	// init_test_struct(&pipeline);
	char *args[] = {"echo", "-n", "hello world", NULL};
	
	pipeline.cmd.argv = args;

	printf("Test: parser_test.c\n");
	printf("_________________________________________________\n");
	printf("1st_cmd\n");
	printf("\n");
	printf("argv -> [\"%s\", \"%s\", \"%s\", NULL]\n", pipeline.cmd.argv[0], pipeline.cmd.argv[1], pipeline.cmd.argv[2]);
	printf("redirs -> NULL\n");
	printf("builtin = ECHO\n");
	printf("_______________________________________________|\n");
	return (0);
}
