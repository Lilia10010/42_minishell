/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:27:15 by meandrad          #+#    #+#             */
/*   Updated: 2025/07/22 22:57:40 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins.h"
#include "lib_ft.h"

int	builtin_env(char **args, t_context *ctx)
{
	int	i;

	if (!ctx->envp || !*ctx->envp)
	{
		ft_putstr_fd("No environment variables set.\n", STDERR_FILENO);
		ctx->exit_status = 1;
		return (1);
	}
	if (args[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		ctx->exit_status = 127;
		return (127);
	}
	i = -1;
	while (ctx->envp[++i])
	{
		if (ft_strchr(ctx->envp[i], '='))
		{
			ft_putstr_fd(ctx->envp[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	ctx->exit_status = 0;
	return (0);
}
//verificar como podemos diminuir o número de linhas sem essa gambiarra feia de i = -1;