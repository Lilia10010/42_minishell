/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:12:25 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/18 21:31:09 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "env.h"
#include "builtin.h"
#include "lib_ft.h"
#include "context_types.h"

static int	check_unset(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(char **args, t_context *ctx)
{
	int	i;

	i = 1;
	ctx->exit_status = 0;
	while (args[i])
	{
		if (!check_unset(args[i]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not valid identifier\n", 2);
			ctx->exit_status = 1;
		}
		else
		{
			if (unset_envp_var(ctx, args[i]) != 0)
				ctx->exit_status = 1;
		}
		i++;
	}
	return (ctx->exit_status);
}