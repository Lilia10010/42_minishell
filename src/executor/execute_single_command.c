/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:11:45 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/14 13:07:04 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_types.h"
#include "context_types.h"
#include "executor.h"
#include "command_types.h"

int	execute_single_command(t_command *cmd, t_context *ctx)
{
	   if (!cmd->args || !cmd->args[0])
    {
        // Se tem redirecionamentos mas não tem comando, executa apenas os redirecionamentos
        if (cmd->output_file || cmd->input_file || cmd->heredoc_mode)
        {
            int original_stdin, original_stdout;
            
            save_original_fds(&original_stdin, &original_stdout);
            if (!aplly_redirection(cmd))
            {
                restore_original_fds(original_stdin, original_stdout);
                ctx->exit_status = 1;
                return (1);
            }
            restore_original_fds(original_stdin, original_stdout);
            ctx->exit_status = 0;
            return (0);
        }
        // Se não tem nem comando nem redirecionamentos, não faz nada
        ctx->exit_status = 0;
        return (0);
    }
	if (get_builtin_id(cmd->args[0]) != BUILTIN_NONE)
		return (execute_builtin_with_redirection(cmd, ctx));
	else
		return (execute_external_command_with_redirectons(cmd, ctx));
}
