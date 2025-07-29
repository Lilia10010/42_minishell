/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:16:50 by meandrad          #+#    #+#             */
/*   Updated: 2025/07/29 18:04:31 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin.h"
#include "lib_ft.h"

static int	is_valid_exit_code(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_context *ctx)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args[2])
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", STDERR_FILENO);
		ctx->exit_status = 1;
		return (1);
	}
	if (args[1] && !is_valid_exit_code(args[1]))
	{
		ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	if (args[1])
		ctx->exit_status = (unsigned char)ft_atoll(args[1]);
	exit(ctx->exit_status);
}
