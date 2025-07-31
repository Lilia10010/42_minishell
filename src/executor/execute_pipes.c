/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:06:14 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/31 18:27:52 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "executor.h"
#include "context_types.h"
#include "command_types.h"
#include "builtin_types.h"

/* int	execute_pipe(t_command *commands, t_context *ctx)
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
 */

int	execute_pipe(t_command *commands, t_context *ctx)
{
	printf("pipeeeeeeeeeeeeeee\n");
	t_command	*current = commands;
	int			pipe_fd[2];
	int			prev_fd = -1;
	pid_t		pid;
	int			status;

	while (current)
	{
		// Se não for o último comando, criamos um pipe
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
		else if (pid == 0) // Processo filho
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (current->next)
			{
				close(pipe_fd[0]); // fechar leitura
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			if (!aplly_redirection(current))
				exit(1);

			if (get_builtin_id(current->args[0]) != BUILTIN_NONE)
				exit(execute_builtin_with_redirection(current, ctx));
			else
				exit(execute_external_command_with_redirectons(current, ctx));
		}

		// Processo pai
		if (prev_fd != -1)
			close(prev_fd);
		if (current->next)
		{
			close(pipe_fd[1]); // fechar escrita
			prev_fd = pipe_fd[0];
		}
		current = current->next;
	}

	// Esperar todos os filhos
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			ctx->exit_status = WEXITSTATUS(status);
	}
	return (0);
}
