/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:35:32 by meandrad          #+#    #+#             */
/*   Updated: 2025/07/16 21:58:02 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include "builtins.h"

int	builtin_pwd(t_context *ctx)
{
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
