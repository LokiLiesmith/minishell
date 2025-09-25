/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel <mel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 01:06:43 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/25 17:46:43 by mel              ###   ########.fr       */
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
	cmd->argv[1] = strdup("-l");
	cmd->argv[2] = NULL;
	cmd->redirs = malloc(sizeof(t_redir_node));
	cmd->redirs->next = NULL;
	cmd->redirs->r.type = R_OUT;
	cmd->redirs->r.target = strdup("test.txt");
	cmd_node->cmd = cmd;

	// ---- Execute ----
	execute_start(cmd_node, env1);
}