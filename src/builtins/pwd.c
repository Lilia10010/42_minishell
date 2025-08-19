/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:35:32 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/19 15:38:43 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "context_types.h"
#include "builtin.h"
#include "lib_ft.h"

int	builtin_pwd(char **args, t_context *ctx)
{
	(void)args;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ctx->exit_status = 1;
		return (1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(pwd);
	ctx->exit_status = 0;
	return (0);
}
