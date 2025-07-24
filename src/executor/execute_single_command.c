/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:16:52 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/23 22:28:56 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <sys/types.h> // Required for pid_t
#include "minishell.h"
#include "parser.h"
#include "builtins.h"
#include "executor.h"
#include "lib_ft.h"


// static int apply_redirections(t_command *cmd)
// {
//     printf("Applying command: %s\n", cmd->args[0]);
// 	return (1); 
// }

int execute_single_command(t_command *cmd, t_context *ctx)
{	
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ctx->exit_status = 0;
		return (0);
		//return (ctx->exit_status = 0, 0); pode?
	}
	if (get_builtin_id(cmd->args[0]) != BUILTIN_NONE)
		return (builtin_dispatcher(cmd, ctx));
	if (is_path_comman(cmd->args[0]))
		return (execute_path_command(cmd, ctx));
	return (execute_command_from_path(cmd, ctx));

}
