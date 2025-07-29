/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:58:24 by meandrad          #+#    #+#             */
/*   Updated: 2025/07/29 18:04:31 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin.h"
#include "lib_ft.h"

static char	*get_pwd(char **envp, char *s)
{
	int	i;
	//char *home;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], s, ft_strlen(s)) == 0)
			return ((ft_strchr(envp[i], '=') + 1));
		i++;
	}
	return (NULL);
}

int	builtin_cd(char **args, t_context *ctx)
{
	char *caminho;

	if (!args[1] || (ft_strncmp(args[1], "~", 1) == 0))
		caminho = get_pwd (ctx->envp, "HOME");
	else
		caminho = args[1];
	if (!caminho)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", STDERR_FILENO);
		ctx->exit_status = 1;
		return (1);
	}
	return (0);
}
