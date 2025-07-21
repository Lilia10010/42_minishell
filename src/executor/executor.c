/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:20:59 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/20 22:29:21 by lpaula-n         ###   ########.fr       */
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

// char *find_executable_in_path(const char *cmd)
// {
// 	char	*path_env;
// 	char	**paths;
// 	char	*full_path;
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	if (!cmd || cmd[0] == '\0')
// 		return (NULL);
// 	path_env = getenv("PATH");
// 	if (!path_env)
// 		return (NULL);
// 	paths = ft_split(path_env, '		// comando absoluto:');
// 	if (!paths)
// 		return (NULL);
// 	while (paths[i])
// 	{
// 		full_path = ft_strjoin(paths[i], "/");
// 		if (!full_path)
// 		{
// 			ft_free_split(paths);
// 			return (NULL);
// 		}
// 		temp = ft_strjoin(full_path, cmd);
// 		free(full_path);
// 		if (!temp)
// 		{
// 			ft_free_split(paths);
// 			return (NULL);
// 		}
// 		if (access(temp, X_OK) == 0)
// 		{
// 			ft_free_split(paths);
// 			return (temp);
// 		}
// 		free(temp);
// 		i++;
// 	}
// 	ft_free_split(paths);
// 	return (NULL);

// }

int execute_single_command(t_command *cmd, t_context *ctx)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		ctx->exit_status = 0;
		return (0);
		//return (ctx->exit_status = 0, 0);
	}
	if (get_builtin_id(cmd->args[0]) != BUILTIN_NONE)
		return (builtin_dispatcher(cmd, ctx));
	if (cmd->args[0][0] == '/')
	{
		//ex : return (execute_external_command(cmd, ctx));
		return printf("==> p/ comando absoluto: %s\n", cmd->args[0]);
	}
	if (ft_strchr(cmd->args[0], '/'))
		return (printf("===> p/ comando relativo: %s\n", cmd->args[0]));
	path = find_executable_in_path(cmd->args[0]);
	if (path)
	{
		printf("==> entrou comando externo: %s\n", path);
		free(path);
		return (1);
	}
	ctx->exit_status = 127; // Comando não encontrado
	return (1);	
}

int execute_pipeline(t_command *commands, t_context *ctx)
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