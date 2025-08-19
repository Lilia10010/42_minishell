/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable_in_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:47:45 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/19 10:46:56 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "executor.h"
#include "lib_ft.h"
#include "env.h"

static char	*join_path(const char *dir, const char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full = ft_strjoin(temp, cmd);
	if (!full)
		return (NULL);
	free(temp);
	return (full);
}
char	*find_executable_in_path(char *cmd, t_context *ctx)
{
	char	*path_env;
	char	**paths;
	char	*full;
	int		i;
	char	*result;

	result = NULL;
	if (!cmd || !*cmd)
		return (NULL);
	path_env = get_env_value("PATH", ctx);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
		{

			result = full;
			break ;
		}
		free(full);
		i++;
	}
	ft_free_split(paths);
	return (result);
}
