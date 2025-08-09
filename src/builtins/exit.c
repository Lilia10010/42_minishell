/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:16:50 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/09 18:07:08 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "builtin.h"
#include "lib_ft.h"
#include "context_types.h"
#include "minishell.h"

static void close_all_fds(void)
{
    int fd;

    for (fd = 3; fd < 1024; fd++)
        close(fd);
}

static void internal_exit(t_context *ctx)
{
    cleanup_context(ctx);
    clear_history();
    rl_clear_history();
    rl_free_line_state();
	close_all_fds();
}

static int	check_digit(char *arg)
{
	if (!arg || !*arg)
		return (0);
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	builtin_exit(char **args, t_context *ctx)
{
	int	exit_code = 0;

	if (!args[1])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		internal_exit(ctx);
		exit(ctx->exit_status);
	}

	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		ctx->exit_status = 1;
		internal_exit(ctx);
		return (1);
	}

	if (!check_digit(args[1]))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		internal_exit(ctx);
		exit(2);
	}

	exit_code = ft_atoi(args[1]) % 256;
	ctx->exit_status = exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	internal_exit(ctx);
	exit(exit_code);
}
