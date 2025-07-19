
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
	if (id_builtin == BUILTIN_PWD)
		return (builtin_pwd(cmd->args, ctx));
	if (id_builtin == BUILTIN_EXPORT)
		return (builtin_export(cmd->args, ctx));
	if (id_builtin == BUILTIN_UNSET)
		return (builtin_unset(cmd->args, ctx));
	if (id_builtin == BUILTIN_ENV)
		return (builtin_env(cmd->args, ctx));
	if (id_builtin == BUILTIN_EXIT)
		return (builtin_exit(cmd->args, ctx));
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

char *find_executable_in_path(const char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
		{
			ft_free_split(paths);
			return (NULL);
		}
		temp = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!temp)
		{
			ft_free_split(paths);
			return (NULL);
		}
		if (access(temp, X_OK) == 0)
		{
			ft_free_split(paths);
			return (temp);
		}
		free(temp);
		i++;
	}
	ft_free_split(paths);
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
		printf("==> entrou comando externo: %s\n", full_path);
		//cmd->args[0] = full_path; // p/ atualizar o comando com o caminho completo, mas talvez isto não seja necessário
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