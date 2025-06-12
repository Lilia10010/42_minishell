
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
    
    // Aqui você pode adicionar outros builtins futuramente:
    // if (strcmp(cmd, "cd") == 0)
    //     return (1);
    // if (strcmp(cmd, "pwd") == 0)
    //     return (1);
    
    return (0);
}

int execute_builtin(t_command *cmd, t_context *ctx)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return (1);
    
    if (strcmp(cmd->args[0], "echo") == 0)
        return (builtin_echo(cmd->args, ctx));
    
    // Aqui você pode adicionar outros builtins futuramente:
    // if (strcmp(cmd->args[0], "cd") == 0)
    //     return (builtin_cd(cmd->args, ctx));
    
    return (1); // Comando não encontrado
}

int execute_command(t_command *commands, t_context *ctx)
{
    if (!commands || !commands->args || !commands->args[0])
    {
        ctx->exit_status = 0;
        return (0);
    }
    
    // Por enquanto, apenas suporta um comando (sem pipes)
    t_command *cmd = commands;
    
    // Verifica se é um builtin
    if (is_builtin(cmd->args[0]))
    {
        return (execute_builtin(cmd, ctx));
    }
    else
    {
        // Comando não é builtin e não implementamos execução externa ainda
        printf("minishell: %s: command not found\n", cmd->args[0]);
        ctx->exit_status = 127; // Código de erro padrão para comando não encontrado
        return (127);
    }
}