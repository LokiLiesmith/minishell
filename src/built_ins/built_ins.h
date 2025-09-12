/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 00:43:43 by msalangi          #+#    #+#             */
/*   Updated: 2025/09/13 01:02:25 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include "../../include/libft/libft.h"
# include "../../include/get_next_line/get_next_line.h"
# include "../../include/minishell.h"

////////////////////////////////////////////////////////////////////////////////
//								 BUILT INS 									  //
////////////////////////////////////////////////////////////////////////////////

int		builtin_cd(t_cmd *cmd, t_env *env);
int		builtin_echo(t_cmd *cmd);
int		builtin_env(t_cmd *cmd, t_env *env);
int		builtin_export(t_cmd *cmd, t_env *env);
int		builtin_pwd(void);
int		builtin_unset(t_cmd *cmd, t_env *env);

# endif