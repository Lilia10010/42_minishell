/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:08:07 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/26 21:00:43 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "parser.h"
#include "minishell.h"
#include "executor.h"

static int	execute_external_command(t_command *cmd, t_context *ctx, char *path)
{
	pid_t	pid;
	int		status;

	printf("entrou aqui execute_external command\n");
	int i = 0 ;
	while (ctx->envp[i])
	{
		printf("envp %s", ctx->envp[i]);
		++i;
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed ");
		ctx->exit_status = 1;
		return (1);
	}
	if (pid == 0)
	{
		execve(path, cmd->args, ctx->envp);
		perror("execve failed");
		ctx->exit_status = 127;
		return (1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ctx->exit_status = WEXITSTATUS(status);
	return (0);
}

int	execute_path_command(t_command *cmd, t_context *ctx)
{
	if (access(cmd->args[0], X_OK) == 0)
		return (execute_external_command(cmd, ctx, cmd->args[0]));
	//STDERR_FILENO
	printf("command not found with path absolut: %s\n", cmd->args[0]);
	ctx->exit_status = 127;
	return (1);
}

int	execute_command_from_path(t_command *cmd, t_context *ctx)
{
	char	*path;
	int		result;

	printf("entrou no execute command from path\n");

	path = find_executable_in_path(cmd->args[0]);
	if (!path)
	{
		//STDERR_FILENO
		printf("comando not found: %s\n", cmd->args[0]);
		ctx->exit_status = 127;
		return (1);
	}
	result = execute_external_command(cmd, ctx, path);
	free(path);
	return (result);
}

