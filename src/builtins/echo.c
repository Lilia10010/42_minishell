/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:35:20 by meandrad          #+#    #+#             */
/*   Updated: 2025/07/31 00:01:49 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"
#include "lib_ft.h"
#include "context_types.h"

static int	valid_flag(char *arg)
{
	int	i;

	i = 1;
	if(!ft_strncmp(arg, "-n", 2))
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static void	echo_args(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}
int	builtin_echo(char **args, t_context *ctx)
{
	int	i;
	int	check_line;

	//verificar se isso aqui é realmente necessário
	if (!args || !*args)
		return (1);
	i = 1;
	check_line = 1;
	while (args[i] && valid_flag(args[i]))
	{
		check_line = 0;
		i++;
	}
	echo_args(args, i);
	if (check_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	ctx->exit_status = 0;
	return(0);
}
