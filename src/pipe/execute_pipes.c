/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:06:14 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/14 15:14:34 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "context_types.h"
#include "command_types.h"
#include "signals.h"
#include "pipe.h"

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
