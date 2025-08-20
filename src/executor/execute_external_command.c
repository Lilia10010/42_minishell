/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:08:07 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/20 19:47:08 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "command_types.h"
#include "context_types.h"
#include "executor.h"
#include "lib_ft.h"
#include "signals.h"
#include "minishell.h"

static void	execute_child_process(t_command *cmd, t_context *ctx, char *path)
{
	setup_signals_child();
	if (!aplly_redirection(cmd, ctx))
	{
		free(path);
		if (cmd->heredoc_mode)
			internal_exit_executor(ctx, 0);
		internal_exit_executor(ctx, 1);
	}
	execve(path, cmd->args, ctx->envp);
	free(path);
	ft_putstr_fd("bash: command not found\n", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	internal_exit_executor(ctx, 127);
}

static int	execute_external_command(t_command *cmd, t_context *ctx, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("", STDERR_FILENO);
		ctx->exit_status = 1;
		return (1);
	}
	if (pid == 0)
		execute_child_process(cmd, ctx, path);
	setup_signals_ignore();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ctx->exit_status = WEXITSTATUS(status);
	else
	{
		ctx->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		}
		else
		{
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	restore_signals();
	return (ctx->exit_status);
}

int	execute_path_command_absolut(t_command *cmd, t_context *ctx)
{
	struct stat	sb;

	if (stat(cmd->args[0], &sb) == -1)
	{
		ft_putstr_fd("bash: command not found\n", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ctx->exit_status = 127;
		return (127);
	}
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		ctx->exit_status = 126;
		return (126);
	}
	if (access(cmd->args[0], X_OK) != 0)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": Permissão negada\n", STDERR_FILENO);
		ctx->exit_status = 126;
		return (126);
	}
	return (execute_external_command(cmd, ctx, cmd->args[0]));
}

int	execute_command_from_path(t_command *cmd, t_context *ctx)
{
	char	*path;
	int		result;

	path = find_executable_in_path(cmd->args[0], ctx);
	if (!path)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ctx->exit_status = 127;
		return (1);
	}
	result = execute_external_command(cmd, ctx, path);
	free(path);
	return (result);
}

int	execute_external_command_with_redirectons(t_command *cmd, t_context *ctx)
{
	if (ft_strchr(cmd->args[0], '/'))
		return (execute_path_command_absolut(cmd, ctx));
	else
		return (execute_command_from_path(cmd, ctx));
	return (1);
}
