
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
	// demais builtins
	return (1); // Comando não encontrado
}

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

	return (execute_pipeline(commands, ctx));
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
char *find_executable_in_path(const char *cmd)
{
	// [] implemntar busca de executável no PATH
	printf("==> buscando executável no PATH: %s\n", cmd);
	char *path_env = getenv("PATH");
	//imprimir o path_env
	printf(" PATH: %s\n", path_env);
	return (NULL);
}
int execute_single_command(t_command *cmd, t_context *ctx)
{
	t_builtin	id_builtin;
	char		*full_path;	

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ctx->exit_status = 0;
		return (0);
	}
	id_builtin = get_builtin_id(cmd->args[0]);
	if (id_builtin != BUILTIN_NONE)
		return (execute_builtin(cmd, ctx));

	if (cmd->args[0][0] == '/')
	{
		// comando absoluto
		//ex : return (execute_external_command(cmd, ctx));
		return printf("==> p/ comando absoluto: %s\n", cmd->args[0]);
	}
	if (ft_strchr(cmd->args[0], '/'))
	{
		// caminho relativo
		//ex: return (execute_external_command(cmd, ctx));
		return printf("==> p/ relativo: %s\n", cmd->args[0]);
	}
	//burcar no path
	full_path = find_executable_in_path(cmd->args[0]);
	if (full_path)
	{
		printf("==> entrou comando externo: %s\n", cmd->args[0]);
		cmd->args[0] = full_path; // p/ atualizar o comando com o caminho completo, mas talvez isto não seja necessário
		// [] implementar execução de comandos externos com execve()
		// [] verificar se o comando é um executável válido
		//execute_external_command(cmd, ctx);
		free(full_path);
		return (1);
	}
	
	ctx->exit_status = 127; // Comando não encontrado
	return (1);	
}



int execute_pipeline(t_command *commands, t_context *ctx)
{
	(void)commands;
	(void)ctx;
	if (!commands)
	{
		ctx->exit_status = 0;
		return (0);
	}

	//[] implementação do pipe
	//[] criação do processo filho
	//[] dentro do processo filho verificar se é builtin ou se é execve

	ctx->exit_status = 127;
	return (1);
}