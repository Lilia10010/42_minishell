/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aplly_heredoc_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:34:38 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/15 21:15:29 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "redirection.h"
#include "signals.h"
#include "command_types.h"
#include "lib_ft.h"
#include "context_types.h"
#include "utils.h"

static int	create_pipe_and_fork(int pipefd[2], pid_t *pid)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (0);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return (0);
	}
	return (1);
}

static void	handle_eof_or_delimiter(char *line,
	t_command *cmd, int writefd, t_context *ctx)
{
	if (!line)
	{
		handle_message_end_of_file(cmd->heredoc_delimiter);
		close(writefd);
		internal_exit_heredoc(ctx, 0);
	}
	if (ft_strcmp(line, cmd->heredoc_delimiter) == 0)
	{
		free(line);
		close(writefd);
		internal_exit_heredoc(ctx, 0);
	}
}

static void	child_heredoc_loop(int writefd, t_command *cmd, t_context *ctx)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		handle_eof_or_delimiter(line, cmd, writefd, ctx);
		line = process_line_expansion(line, ctx);
		dprintf(writefd, "%s\n", line);
		free(line);
	}
}

static int	parent_setup_and_wait(int readfd, int writefd,
	pid_t pid, t_context *ctx)
{
	int	status;

	(void)writefd;
	close(writefd);
	if (dup2(readfd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(readfd);
		return (0);
	}
	close(readfd);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ctx->exit_status = 130;
		g_signal_received = -1;
		return (0);
	}
	return (1);
}

int	aplly_heredoc_redirection(t_command *cmd, t_context *ctx)
{
	int		pipefd[2];
	pid_t	pid;

	if (!cmd || !cmd->heredoc_delimiter)
	{
		fprintf(stderr, "HEREDOC ERROR: cmd ou delimiter é NULL\n");
		return (0);
	}
	if (!create_pipe_and_fork(pipefd, &pid))
		return (0);
	if (pid == 0)
	{
		close(pipefd[0]);
		child_heredoc_loop(pipefd[1], cmd, ctx);
	}
	return (parent_setup_and_wait(pipefd[0], pipefd[1], pid, ctx));
}
