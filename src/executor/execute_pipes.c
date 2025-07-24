/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:06:14 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/22 23:17:15 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "parser.h"
#include "minishell.h"

int	execute_pipe(t_command *commands, t_context *ctx)
{
	t_command *current;

	current = commands;
	if (!commands)
	{
		ctx->exit_status = 0;
		return (0);
	}
	while (current)
	{
		int i = 0;
		while (i < current->arg_count)
		{
			printf("argd =>> %s\n", current->args[i]);
			++i;
		}
		current = current->next;
	}

	//[] implementação do pipe
	//[] criação do processo filho
	//[] dentro do processo filho verificar se é builtin ou se é execve

	ctx->exit_status = 127;
	return (1);
}
