/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:16:50 by meandrad          #+#    #+#             */
/*   Updated: 2025/07/31 00:01:14 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin.h"
#include "lib_ft.h"
#include "context_types.h"


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
		exit(ctx->exit_status);
	}

	if (args[2])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("Minishell: exit: too many arguments\n", STDERR_FILENO);
		ctx->exit_status = 1;
		return (1);
	}

	if (!check_digit(args[1]))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2); // mesmo comportamento que seu exemplo funcional
	}

	exit_code = ft_atoi(args[1]) % 256;
	ctx->exit_status = exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}
