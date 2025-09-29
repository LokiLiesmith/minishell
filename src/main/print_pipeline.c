#include "minishell.h"

// static const char *builtin_str(t_builtin b)
// {
// 	if (b == ECHO)   return "ECHO";
// 	if (b == CD)     return "CD";
// 	if (b == PWD)    return "PWD";
// 	if (b == EXPORT) return "EXPORT";
// 	if (b == UNSET)  return "UNSET";
// 	if (b == ENV)    return "ENV";
// 	if (b == EXIT)   return "EXIT";
// 	return "NONE";
// }

// static const char *redir_type_str(t_redir_type t)
// {
// 	if (t == R_IN)      return "<";
// 	if (t == R_OUT)     return ">";
// 	if (t == R_APPEND)  return ">>";
// 	if (t == R_HEREDOC) return "<<";
// 	return "?";
// }

// static void    print_redirs(const t_redir_node *head)
// {
//     const t_redir_node *cur;

//     // printf("Redirs:\n");
//     cur = head;
//     while (cur)
//     {
//         printf("    %s %s", redir_type_str(cur->r.type),
//         cur->r.target ? cur->r.target : "(null)");
// 		/* If you store an opened fd, show it for debug */
// 		// if (cur->r.fd == 0 || cur->r.fd == 1 || cur->r.fd == 2)
// 		// 	printf("  [fd=%d]", cur->r.fd);
//         if (cur->r.fd == 0 || cur->r.fd == -1)
//         	printf("  [fd=%d]", cur->r.fd);

// 		printf("\n");
//         cur = cur->next;
//     }
// }

// void    print_pipeline(const t_cmd_node *pipeline)
// {

//     const t_cmd_node *node;
//     int         i;

//     node = pipeline;
//     while (node)
//     {
//         printf("=== Command ===\n");
//         if (node->cmd->argv && node->cmd->argv[0])
//         {
//             i = 0;
//             while (node->cmd->argv[i])
//             {
//                 printf("argv[%d]: %s\n", i, node->cmd->argv[i]);
//                 i++;
//             }
            
//         }
//         else
//             printf("None\n");

//         print_redirs(node->cmd->redirs);
//         printf("builtin: %s (%d)\n", builtin_str(node->cmd->builtin), node->cmd->builtin);
//         printf("===============\n");
//         node = node->next;
//     }
// }
