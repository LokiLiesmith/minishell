/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:59:34 by mel               #+#    #+#             */
/*   Updated: 2025/10/02 22:11:24 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ORIGINAL
// int	builtin_unset(t_cmd *cmd, t_env *env)
// {
// 	t_env	*current;
// 	t_env	*temp;
// 	int		i;

// 	current = env;
// 	i = 1;
// 	// if (cmd->argv[1] == NULL)
// 	// 	return (1);

// 	while (cmd->argv[i] != NULL)
// 	{
// 		while (current->next->next != NULL && ft_strncmp(current->next->type, cmd->argv[i], ft_strlen(cmd->argv[i])))
// 			current = current->next;
// 		if (current->next->next == NULL && ft_strncmp(current->next->type, cmd->argv[i], ft_strlen(cmd->argv[i])) == 0)
// 		{
// 			temp = current->next;
// 			current->next = NULL;
// 		}
// 		else if (current->next != NULL && ft_strncmp(current->next->type, cmd->argv[i], ft_strlen(cmd->argv[i])) == 0)
// 		{
// 			temp = current->next->next;
// 			current->next = temp;
// 		}
// 		i++;
// 	}
// 	return (0);
// }


///GPT MONOLOGUE XD
// Head removal:
// If the variable to unset is at the head of the list (env itself),
// your code never removes it because you always look at current->next.

// Traversal logic:
// You stop at current->next->next != NULL, which makes things 
// tricky and risks skipping the last node.

// Temp variable not freed:
// You unlink nodes but never free them. Even though you use gc_malloc,
// if you want to keep GC clean, you either (a) leave it dangling and 
// rely on GC cleanup on exit, or (b) explicitly
// unlink only. Either way, your logic should at least unlink properly.

// Partial matches:
// You use ft_strncmp(..., ft_strlen(cmd->argv[i])).
// That means unset P could match PATH. You need ft_strcmp for exact matches.

//GPT PROPOSED CHANGES

#include "../../include/minishell.h"

static int is_valid_identifier(const char *s)
{
    int i = 0;

    if (!s || (!ft_isalpha((unsigned char)s[0]) && s[0] != '_'))
        return 0;
    while (s[i])
    {
        if (!ft_isalnum((unsigned char)s[i]) && s[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

int builtin_unset(t_cmd *cmd, t_env **envp)
{
    int   i = 1;
    int   err = 0;

    while (cmd->argv[i])
    {
        if (!is_valid_identifier(cmd->argv[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(cmd->argv[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
            err = 1;
            i++;
            continue;
        }

        t_env *prev = NULL;
        t_env *cur  = *envp;
        while (cur)
        {
            if (ft_strcmp(cur->type, cmd->argv[i]) == 0)
            {
                // unlink
                if (prev)
                    prev->next = cur->next;
                else
                    *envp = cur->next;  // removing head
                break;
            }
            prev = cur;
            cur  = cur->next;
        }
        i++;
    }
    return err;
}