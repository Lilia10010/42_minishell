/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:58:24 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/17 21:56:28 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtin.h"
#include "lib_ft.h"
#include "context_types.h"

static void	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
}

static char	*get_target_path(char **args, char **envp)
{
	char	*home_path;

	if (!args[1])
	{
		home_path = get_env_value("HOME", envp);
		if (!home_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (ft_strdup(home_path));
	}
	return (ft_strdup(args[1]));
}

static int	update_path_var(char **envp, char *old_path)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (1);
	if (set_env(envp, "OLDPWD", old_path) != 0)
	{
		free(new_path);
		return (1);
	}
	if (set_env(envp, "PWD", new_path) != 0)
	{
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

static int	change_directory(char *path, char **envp)
{
	char	*old_path;
	int		result;

	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (1);
	if (chdir(path) != 0)
	{
		cd_error(path);
		free(old_path);
		return (1);
	}
	result = update_path_var(envp, old_path);
	free(old_path);
	return (result);
}

int	builtind_cd(char **args, t_context *ctx)
{
	char	*target_path;
	int		result;

	target_path = get_target_path(args, ctx->envp);
	if (!target_path)
	{
		ctx->exit_status = 1;
		return (1);
	}
	result = change_directory(target_path, ctx->envp);
	free(target_path);
	ctx->exit_status = result;
	return (result);
}
