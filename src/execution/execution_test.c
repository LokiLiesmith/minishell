/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 01:06:43 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/13 01:07:19 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int main(void) {
	// ---- Create mock environment ----
	t_env *env1 = malloc(sizeof(t_env));
	t_env *env2 = malloc(sizeof(t_env));

	env1->type = strdup("PATH");
	env1->value = strdup("/bin:/usr/bin");
	env1->next = env2;

	env2->type = strdup("HOME");
	env2->value = strdup("/home/user");
	env2->next = NULL;

	// ---- Create command node for `ls -l` ----
	t_cmd_node *cmd_node = malloc(sizeof(t_cmd_node));
	cmd_node->next = NULL;

	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->argv = malloc(sizeof(char *) * 3);
	cmd->argv[0] = strdup("ls");
	cmd->argv[1] = NULL;
	cmd_node->cmd = cmd;

	// ---- Execute ----
	execute_start(cmd_node, env1);
}