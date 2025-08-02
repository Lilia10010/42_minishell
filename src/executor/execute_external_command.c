/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:08:07 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/01 21:52:57 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "command_types.h"
#include "context_types.h"
#include "executor.h"

static int	execute_external_command(t_command *cmd, t_context *ctx, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed ");
		ctx->exit_status = 1;
		return (1);
	}
	if (pid == 0)
	{
		if (!aplly_redirection(cmd))
			exit(1);
		execve(path, cmd->args, ctx->envp);
		perror("execve failed");
		exit(127);
		return (1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ctx->exit_status = WEXITSTATUS(status);
	return (0);
}

int	execute_path_command_absolut(t_command *cmd, t_context *ctx)
{
	if (access(cmd->args[0], X_OK) == 0)
		return (execute_external_command(cmd, ctx, cmd->args[0]));
	//STDERR_FILENO
	ctx->exit_status = 127;
	return (1);
}

int	execute_command_from_path(t_command *cmd, t_context *ctx)
{
	char	*path;
	int		result;

	//printf("entrou no execute command from path\n");

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

int execute_external_command_with_redirectons(t_command *cmd, t_context *ctx)
{
	(void)cmd;
	(void)ctx;
	
	if (is_path_comman(cmd->args[0]))
		return (execute_path_command_absolut(cmd, ctx));
	else
		return (execute_command_from_path(cmd, ctx));
	return (1);
	//return (ctx->exit_status = 0);
}

