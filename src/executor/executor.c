
// TODO
// [] mplementar execução de comandos externos com execve()
// [] adicionar suporte a pipes
// [] implementar redirecionamentos
// [] gerenciar processos filho

#include "executor.h"
#include "builtins.h"
#include <string.h>
#include <stdio.h>
#include "minishell.h"


t_builtin get_builtin_id(char *cmd)
{
	
    if (!cmd)
        return (BUILTIN_NONE);
    if (strcmp(cmd, BUILTIN_NAME_ECHO) == 0)
		return (BUILTIN_ECHO);
	if (strcmp(cmd, BUILTIN_NAME_CD) == 0)
        return (BUILTIN_CD);
	if (strcmp(cmd, BUILTIN_NAME_PWD) == 0)
        return (BUILTIN_PWD);
	if (strcmp(cmd, BUILTIN_NAME_EXPORT) == 0)
        return (BUILTIN_EXPORT);
	if (strcmp(cmd, BUILTIN_NAME_UNSET) == 0)
        return (BUILTIN_UNSET);
	if (strcmp(cmd, BUILTIN_NAME_ENV) == 0)
        return (BUILTIN_ENV);
	if (strcmp(cmd, BUILTIN_NAME_EXIT) == 0)
        return (BUILTIN_EXIT);
    return (BUILTIN_NONE);
}

int execute_builtin(t_command *cmd, t_context *ctx)
{
	t_builtin id_builtin;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (1);
    id_builtin = get_builtin_id(cmd->args[0]);
    if (id_builtin == BUILTIN_ECHO)
		return (builtin_echo(cmd->args, ctx));
	if (id_builtin == BUILTIN_CD)
		return (builtin_cd(cmd->args, ctx));
    //demais builtins
    return (1); // Comando não encontrado
}

int execute_command(t_command *commands, t_context *ctx)
{
	 //if (!commands || !commands->args || !commands->args[0] verificar se tratar dps é melhor
    if (!commands)
    {
       // ctx->exit_status = 0;
        return (0);
    }
    
    if (!commands->next)
		return (execute_single_command(commands, ctx));

	return (execute_pipeline(commands, ctx));
}

int execute_single_command(t_command *cmd, t_context *ctx)
{
	t_builtin id_builtin;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ctx->exit_status = 0;
		return (0);
	}
	id_builtin = get_builtin_id(cmd->args[0]);
	if (id_builtin != BUILTIN_NONE)
		return (execute_builtin(cmd, ctx));
	
	//implementar comandos externo - fork e tals para executar execve e a funcionalidades com comando PATH

	//retirar este return dps que implementar as funções acima
	return (0);
}

int execute_pipeline(t_command *commands, t_context *ctx)
{
	 // Debug completo da pipeline
    DEBUG_FULL(commands, ctx);
	int i = 0;
	
	(void)commands;
	(void)ctx;
	//[] implementação do pipe
	//[] criação do processo filho
	//[] dentro do processo filho verificar se é builtin ou se é execve  
	return (0);
}