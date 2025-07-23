
#include <stdio.h>
#include "parser.h"
#include "minishell.h"

int	execute_external_command(t_command *cmd, t_context *ctx)
{
	// [] implementar execução de comandos externos com execve()
	int i;

	i = 0;
	while (cmd->args[i])
	{
		printf("==> comando externo: %s\n", cmd->args[i]);
		i++;
	}
	//printf("==> comando externo não implementado: %s\n", cmd->args[0]);
	// retornar erro de comando não encontrado
	ctx->exit_status = 127; // Comando não encontrado
	return (1);

}