/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:10:22 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/05 18:06:04 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "redirection.h"
#include "command_types.h"
#include "executor.h"

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

	int i = 0;
	if (!cmd->output_file)
		return (1);
	if (cmd->append_mode)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	for (i = 0; i < cmd->output_file_count; i++)
    {
        fd = open(cmd->output_file[i], flags, 0644);
        if (fd == -1)
        {
            perror(cmd->output_file[i]);
            return (0);
        }
        // Apenas o último arquivo recebe o redirecionamento
        if (i == cmd->output_file_count - 1)
        {
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("ERROR: aplly output redirection dup2");
                close(fd);
                return (0);
            }
        }
        close(fd); // Fechar o arquivo após criar ou redirecionar
    }
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
	if (cmd->output_file)
	{
		if (!aplly_output_redirection(cmd))
			return (0);
	}
	if (cmd->input_file)
	{
		if (!aplly_input_redirection(cmd))
		return (0);
	}
	return (1);
}

void save_original_fds(int *fd_stdin, int *fd_stdout)
{
	*fd_stdin = dup(STDIN_FILENO);
	*fd_stdout = dup(STDOUT_FILENO);
}

void restore_original_fds(int fd_stdin, int fd_stdout)
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







//ver a questão do save e reste * &