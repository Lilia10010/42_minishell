/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:10:22 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/28 23:01:10 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#include "redirection.h"
#include "parser.h"

static int aplly_input_redirection(t_command *cmd)
{
	(void)cmd;
	int fd;

	if (!cmd->input_file)
		return (1);
	fd = open(cmd->input_file, O_RDONLY);
	if (fd == -1)
	{
		perror(cmd->input_file);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("ERROR: aplly input redirectio dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int aplly_output_redirection(t_command *cmd)
{
	int	fd;
	int	flags;

	if (!cmd->output_file)
		return (1);
	if (cmd->append_mode)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(cmd->output_file, flags, 0644);
	if (fd == -1)
	{
		perror(cmd->output_file);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("ERROR: apply output redirect");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

//criar a função do heredoc
static int aplly_heredoc_redirection(t_command *cmd)
{
	(void)cmd;
	printf("nos redirects HEREDOC");
	return (1);
}

int aplly_redirection(t_command *cmd)
{
	if (!cmd)
		return (1);
	if (cmd->heredoc_mode)
	{
		if (!aplly_heredoc_redirection(cmd))
			return (0);
	}
	if (cmd->input_file)
	{
		if (! aplly_input_redirection(cmd))
		return (0);
	}
	if (cmd->output_file)
	{
		if (!aplly_output_redirection(cmd))
			return (0);
	}
	return (1);
}

int			execute_single_command(t_command *cmd, t_context *ctx)
{
	(void)cmd;
	(void)ctx;
	printf("cu =>>");
	return (1);
}

static void save_original_fds(int *fd_stdin, int *fd_stdout)
{
	*fd_stdin = dup(STDIN_FILENO);
	*fd_stdout = dup(STDOUT_FILENO);
}

static void restore_original_fds(int fd_stdin, int fd_stdout)
{
	if (fd_stdin != -1)
	{
		dup2(fd_stdin, STDIN_FILENO);
		close(fd_stdin);
	}
	if (fd_stdout != -1)
	{
		dup2(fd_stdout, STDOUT_FILENO);
		close(fd_stdout);
	}
}

//builtin sem fork e com redirect
static int	execute_builtin_with_redirection(t_command *cmd, t_context *ctx)
{
	int	original_stdin;
	int	original_stdout;
	int	result;

	save_original_fds(&original_stdin, &original_stdout);
	if (!aplly_redirection(cmd))
	{
		restore_original_fds(&original_stdin, &original_stdout);
		
	}



	return (1);
}
