/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:32:43 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/17 21:31:26 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

int	check_envp_params(char **envp, char *name)
{
	if (!envp || !*envp || !name || !*name)
		return (-1);
	return (0);
}

void	free_cpy_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

int	get_envp_index(char *key, char **envp)
{
	int	i;
	int	key_lenght;

	i = 0;
	key_lenght = ft_strlen(key);
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], key, key_lenght) == 0)
		{
			if (envp[i][key_lenght] == '=' || envp[i][key_lenght] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**create_new_env_var(char **old_envp, char *var, int size, int i)
{
	char	**new_envp;

	new_envp = ft_calloc(size + 2, sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (old_envp && old_envp[i])
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[--i]);
			return (free(new_envp), NULL);
		}
		i++;
	}
	new_envp[i] = ft_strdup(var);
	if (!new_envp[i])
	{
		while (i > 0)
			free(new_envp[--i]);
		return (free(new_envp), NULL);
	}
	return (new_envp);
}
