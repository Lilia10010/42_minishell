/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:16:50 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/18 22:10:10 by meandrad         ###   ########.fr       */
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

	fd = 3;
	while(fd < 1024)
	{
		close(fd);
		fd++;
	}
}

static void exit_error(char *arg)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
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
		return (exit_code);
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
		exit_error(args[1]);
		internal_exit(ctx);
		return (2);
	}
	exit_code = ft_atoi(args[1]) % 256;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	internal_exit(ctx);
	return (exit_code);
}
