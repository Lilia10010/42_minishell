/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:20:59 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/31 00:38:06 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "executor.h"
#include "command_types.h"

int execute_command(t_command *commands, t_context *ctx)
{
	// if (!commands || !commands->args || !commands->args[0] verificar se tratar dps é melhor
	printf("entrou no executor xxxxxxxxxxxx\n");
	if (!commands)
	{
		// ctx->exit_status = 0;
		return (0);
	}
	if (!commands->next)
		return (execute_single_command(commands, ctx));
	return (execute_pipe(commands, ctx));
}
