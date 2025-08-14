/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:06:14 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/14 13:05:51 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "executor.h"
#include "context_types.h"
#include "command_types.h"
#include "builtin_types.h"
#include "signals.h"
#include "minishell.h"
#include "lib_ft.h"
#include "utils.h"

static void	internal_exit(t_context *ctx, int code)
{
	cleanup_context(ctx);
	clear_history();
	rl_clear_history();
	rl_free_line_state();
	exit(code);
}

static int	handle_pipe_creation(int pipe_fd[2], t_command *current)
{
	if (current->next && pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (1);
	}
	return (0);
}

static int	handle_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	return (pid);
}

static void	setup_child_input(int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

static void	setup_child_output(t_command *current, int pipe_fd[2])
{
	if (current->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

static void	handle_stderr_redirect(t_command *current, int prev_fd)
{
	int	dev_null;

	if (current->next && prev_fd == -1)
	{
		dev_null = open("/dev/null", O_WRONLY);
		if (dev_null != -1)
		{
			dup2(dev_null, STDERR_FILENO);
			close(dev_null);
		}
	}
}

static void	execute_child_process(t_command *current, t_context *ctx)
{
	int	builtin_id;
	int	exit_code;

	if (!aplly_redirection(current))
		internal_exit(ctx, 1);
	builtin_id = get_builtin_id(current->args[0]);
	if (builtin_id != BUILTIN_NONE)
	{
		exit_code = execute_builtin_with_redirection(current, ctx);
		internal_exit(ctx, exit_code);
	}
	else
	{
		exit_code = execute_external_command_with_redirectons(current, ctx);
		internal_exit(ctx, exit_code);
	}
}

static void	cleanup_parent_fds(int prev_fd, t_command *current, int pipe_fd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (current->next)
		close(pipe_fd[1]);
}

static int	process_single_command(t_command *current, t_context *ctx,
								int *prev_fd, int *last_pid)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (handle_pipe_creation(pipe_fd, current))
		return (1);
	pid = handle_fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		setup_signals_child();
		setup_child_input(*prev_fd);
		setup_child_output(current, pipe_fd);
		handle_stderr_redirect(current, *prev_fd);
		execute_child_process(current, ctx);
	}
	cleanup_parent_fds(*prev_fd, current, pipe_fd);
	if (current->next)
		*prev_fd = pipe_fd[0];
	*last_pid = pid;
	return (0);
}

static void	handle_wait_status(int status, pid_t waited_pid,
							int last_pid, t_context *ctx)
{
	if (WIFEXITED(status) && waited_pid == last_pid)
		ctx->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && waited_pid == last_pid)
		ctx->exit_status = 128 + WTERMSIG(status);
}

static void	wait_for_children(int last_pid, t_context *ctx)
{
	pid_t	waited_pid;
	int		status;

	setup_signals_ignore();
	waited_pid = wait(&status);
	while (waited_pid > 0)
	{
		handle_wait_status(status, waited_pid, last_pid, ctx);
		waited_pid = wait(&status);
	}
	restore_signals();
}

int	execute_pipe(t_command *commands, t_context *ctx)
{
	t_command	*current;
	int			prev_fd;
	int			last_pid;

	current = commands;
	prev_fd = -1;
	last_pid = -1;
	while (current)
	{
		if (process_single_command(current, ctx, &prev_fd, &last_pid))
			return (1);
		current = current->next;
	}
	wait_for_children(last_pid, ctx);
	return (0);
}
