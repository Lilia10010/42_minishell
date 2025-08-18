/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:10:22 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 23:28:49 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "redirection.h"
#include "command_types.h"
#include "executor.h"
#include "lib_ft.h"

static int	aplly_input_redirection(t_command *cmd)
{
	int	fd;

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

static int	open_and_redirect_last_file(t_command *cmd, int flags)
{
	int	i;
	int	fd;

	i = 0;
	while (i < cmd->output_file_count)
	{
		fd = open(cmd->output_file[i], flags, 0644);
		if (fd == -1)
		{
			perror(cmd->output_file[i]);
			return (0);
		}
		if (i == cmd->output_file_count - 1)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("ERROR: aplly output redirection dup2");
				close(fd);
				return (0);
			}
		}
		close(fd);
		i++;
	}
	return (1);
}

static int	aplly_output_redirection(t_command *cmd)
{
	int	flags;

	if (!cmd->output_file)
		return (1);
	if (cmd->append_mode)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	return (open_and_redirect_last_file(cmd, flags));
}

int	aplly_redirection(t_command *cmd, t_context *ctx)
{
	if (!cmd)
		return (1);
	if (cmd->heredoc_mode)
	{
		if (!aplly_heredoc_redirection(cmd, ctx))
		{
			return (0);
		}
	}
	if (cmd->input_file)
	{
		if (!aplly_input_redirection(cmd))
			return (0);
	}
	if (cmd->output_file)
	{
		if (!aplly_output_redirection(cmd))
			return (0);
	}
	return (1);
}
