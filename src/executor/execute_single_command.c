/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:16:52 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/22 22:38:07 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"
#include "parser.h"
#include "builtins.h"
#include "executor.h"
#include "lib_ft.h"

int execute_single_command(t_command *cmd, t_context *ctx)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ctx->exit_status = 0;
		return (0);
		//return (ctx->exit_status = 0, 0);
	}
	if (get_builtin_id(cmd->args[0]) != BUILTIN_NONE)
		return (builtin_dispatcher(cmd, ctx));
	if (cmd->args[0][0] == '/')
	{
		//ex : return (execute_external_command(cmd, ctx));
		return printf("==> p/ comando absoluto: %s\n", cmd->args[0]);
	}
	if (ft_strchr(cmd->args[0], '/'))
		return (printf("===> p/ comando relativo: %s\n", cmd->args[0]));
	path = find_executable_in_path(cmd->args[0]);
	if (path)
	{
		printf("==> entrou comando externo:: %s\n", path);
		free(path);
		return (1);
	}
	ctx->exit_status = 127; // Comando não encontrado
	return (1);	
}