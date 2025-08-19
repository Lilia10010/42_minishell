/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:05:39 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/19 10:20:33 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"
#include "builtin.h"
#include "lib_ft.h"
#include "context_types.h"

static int	valid_char(char c, int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static int	valid_identifier(char *var)
{
	int	i;

	i = 0;
	if (!valid_char(var[0], 1))
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!valid_char(var[i], 0))
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

static int	process_arg(char *arg, t_context *ctx)
{
	if (!valid_identifier(arg))
	{
		export_error(arg);
		return (1);
	}
	if (ft_strchr(arg, '='))
		return (set_env_var(ctx, arg));
	return (0);
}

int	builtin_export(char **args, t_context *ctx)
{
	int	i;

	if (!args[1])
	{
		sorted_envp(ctx->envp);
		return (0);
	}
	i = 1;
	ctx->exit_status = 0;
	while (args[i])
	{
		if (process_arg(args[i], ctx) != 0)
			ctx->exit_status = 1;
		i++;
	}
	return (ctx->exit_status);
}
