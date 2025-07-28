/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:29:26 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/28 18:36:54 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "parser.h"


static int	call_builtin(t_builtin id, t_command *cmd, t_context *ctx)
{
	if (id == BUILTIN_ECHO)
		return (builtin_echo(cmd->args, ctx));
	if (id == BUILTIN_CD)
		return (builtin_cd(cmd->args, ctx));
	if (id == BUILTIN_PWD)
		return (builtin_pwd(cmd->args, ctx));
	if (id == BUILTIN_EXPORT)
		return (builtin_export(cmd->args, ctx));
	if (id == BUILTIN_UNSET)
		return (builtin_unset(cmd->args, ctx));
	if (id == BUILTIN_ENV)
		return (builtin_env(cmd->args, ctx));
	if (id == BUILTIN_EXIT)
		return (builtin_exit(cmd->args, ctx));
	return (1);
}

int	builtin_dispatcher(t_command *cmd, t_context *ctx)
{
	t_builtin id;

	if(!cmd || !cmd->args || !cmd->args[0])
		return (1);
	id = get_builtin_id(cmd->args[0]);
	return (call_builtin(id, cmd, ctx));
}
