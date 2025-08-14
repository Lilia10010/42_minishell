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
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ctx->exit_status = 0;
		return (0);
	}
	if (get_builtin_id(cmd->args[0]) != BUILTIN_NONE)
		return (execute_builtin_with_redirection(cmd, ctx));
	else
		return (execute_external_command_with_redirectons(cmd, ctx));
}
