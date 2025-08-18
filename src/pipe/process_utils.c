
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "pipe.h"
#include "context_types.h"
#include "command_types.h"
#include "builtin_types.h"
#include "signals.h"
#include "executor.h"
#include "minishell.h"
#include "utils.h"

static void	internal_exit(t_context *ctx, int code)
{
	cleanup_context(ctx);
	cleanup_context_envp(ctx);
	clear_history();
	rl_clear_history();
	rl_free_line_state();
	exit(code);
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

static void	handle_stderr_redirect(t_command *current, int prev_fd)
{
	int	dev_null;
	(void)prev_fd;

	if (current->next)
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

int	process_single_command(t_command *current, t_context *ctx,
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
