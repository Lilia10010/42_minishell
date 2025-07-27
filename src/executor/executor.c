/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:20:59 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/26 21:40:57 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// TODO
// [] mplementar execução de comandos externos com execve()
// [] adicionar suporte a pipes
// [] implementar redirecionamentos
// [] gerenciar processos filho

#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include <stdio.h>


int execute_command(t_command *commands, t_context *ctx)
{
	// if (!commands || !commands->args || !commands->args[0] verificar se tratar dps é melhor
	printf("entrou no xxxxxxxxxxxx\n");
	if (!commands)
	{
		// ctx->exit_status = 0;
		return (0);
	}
	if (!commands->next)
		return (execute_single_command(commands, ctx));
	return (execute_pipe(commands, ctx));
}
