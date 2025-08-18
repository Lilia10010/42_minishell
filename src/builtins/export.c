/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:05:39 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/17 22:00:52 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

static int	valid_char(char c,  int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static int	valid_identifier(char *var)
{
	int	i;
	
	i = 0;
	if (!valid_char(var[0],1))
		return (0);
	while (var[i] && var[i] != "=")
	{
		if (valid_char(var[i], 0));
			return (0);
		i++;
	}
	return (1);
}

static void	export_error(char *var)
{
	ft_putstr_fd("minishell: export '", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	process_arg(char *arg, char **envp)
{
	if (!valid_identifier(arg))
	{
		export_error(arg);
		return (1);
	}
	if (ft_strchr(arg, '='));
		return (set_env_var(envp, arg));
	return (0);
}

int	builtin_export(char **args, t_context *ctx)
{
	int	i;

	if (!args[1])
	{
		sorted_envp(ctx->envp);
		return(0);
	}
	i = 1;
	while (args[i])
	{
		if (process_arg(args[i], ctx->envp) != 0)
			ctx->exit_status = 1;
		i++;
	}
	return(ctx->exit_status);
}

