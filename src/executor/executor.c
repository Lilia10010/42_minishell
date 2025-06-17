
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

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    
    if (strcmp(cmd, "echo") == 0)
        return (1);
    
    //  adicionar outros builtins futuramente:
    // if (strcmp(cmd, "cd") == 0)
    //     return (1);
    // if (strcmp(cmd, "pwd") == 0)
    //     return
    
    return (0);
}

int execute_builtin(t_command *cmd, t_context *ctx)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return (1);
    
    if (strcmp(cmd->args[0], "echo") == 0)
        return (builtin_echo(cmd->args, ctx));
    
    //demais builtins
    // if (strcmp(cmd->args[0], "cd") == 0)
    //     return (builtin_cd(cmd->args, ctx));
    
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
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ctx->exit_status = 0;
		return (0);
	}
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd, ctx));
	
	//implementar comandos externo - fork e tals para executar execve e a funcionalidades com comando PATH

	//retirar este return dps que implementar as funções acima
	return (0);
}

int execute_pipeline(t_command *commands, t_context *ctx)
{
	(void)commands;
	(void)ctx;
	//[] implementação do pipe
	//[] criação do processo filho
	//[] dentro do processo filho verificar se é builtin ou se é execve  
	return (0);
}