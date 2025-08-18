/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_or_restore_original_fds.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:39:13 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 21:41:00 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "redirection.h"

void	save_original_fds(int *fd_stdin, int *fd_stdout)
{
	*fd_stdin = dup(STDIN_FILENO);
	*fd_stdout = dup(STDOUT_FILENO);
}

void	restore_original_fds(int fd_stdin, int fd_stdout)
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
