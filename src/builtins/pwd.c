/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:35:32 by meandrad          #+#    #+#             */
/*   Updated: 2025/07/29 18:04:31 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include "builtin.h"
#include <lib_ft.h>
#include <stdio.h>

int	builtin_pwd(char **args, t_context *ctx)
{
	int i = 0;
	while (args[i])
	{
		printf("PWD %s", args[i]);
		++i;
	}
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		//perror("pwd");
		ctx->exit_status = 1;
		return (1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(pwd);
	ctx->exit_status = 0;
	return (0);
}
