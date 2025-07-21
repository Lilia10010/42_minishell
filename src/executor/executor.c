/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:20:59 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/20 23:18:52 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// TODO
// [] mplementar execução de comandos externos com execve()
// [] adicionar suporte a pipes
// [] implementar redirecionamentos
// [] gerenciar processos filho

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "builtins.h"
#include "lib_ft.h"
#include "env.h"


int execute_command(t_command *commands, t_context *ctx)
{
	// if (!commands || !commands->args || !commands->args[0] verificar se tratar dps é melhor
	if (!commands)
	{
		// ctx->exit_status = 0;
		return (0);
	}
	if (!commands->next)
		return (execute_single_command(commands, ctx));

	return (execute_pipe(commands, ctx));
}

void execute_external_command(t_command *cmd, t_context *ctx)
{
	(void)cmd;
	(void)ctx;
	// [] implementar execução de comandos externos com execve()
	printf("==> comando externo não implementado: %s\n", cmd->args[0]);
	ctx->exit_status = 127; // Comando não encontrado
	// retornar erro de comando não encontrado
}
void ft_free_split(char **split)
{
	int i = 0;
	if (!split)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}


