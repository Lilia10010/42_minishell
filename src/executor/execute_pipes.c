/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:06:14 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/11 00:09:13 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
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

static void internal_exit(t_context *ctx, int code)
{
    cleanup_context(ctx);
    clear_history();
    rl_clear_history();
    rl_free_line_state();
	exit(code);
}

int	execute_pipe(t_command *commands, t_context *ctx)
{
	t_command	*current = commands;
	int			pipe_fd[2];
	int			prev_fd = -1;
	pid_t		pid;
	int			status;
	int 		last_pid = -1;
	pid_t 		waited_pid;
	
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
		{
			perror("pipe failed");
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			return (1);
		}
		else if (pid == 0) 
		{
			setup_signals_child();
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (current->next)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			if (!aplly_redirection(current))
				internal_exit(ctx, 1);
			if (get_builtin_id(current->args[0]) != BUILTIN_NONE)
				internal_exit(ctx, execute_builtin_with_redirection(current, ctx));
			else
				internal_exit(ctx, execute_external_command_with_redirectons(current, ctx));
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (current->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		last_pid = pid;
		current = current->next;
	}
	setup_signals_ignore();
	while ((waited_pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status) && waited_pid == last_pid)
			ctx->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && waited_pid == last_pid)
			ctx->exit_status = 128 + WTERMSIG(status);
	}
	restore_signals();
	return (0);
}
