/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:36:38 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/18 21:38:50 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

int	count_envp_vars(char **envp)
{
	int	size;

	size = 0;
	if (!envp)
		return (0);
	while (envp[size])
		size++;
	return (size);
}

static char	**recreate_envp(char **old_envp, int size, int skip_index)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = ft_calloc(size, sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i != skip_index)
		{
			new_envp[i] = ft_strdup(old_envp[i]);
			if (!new_envp[j])
			{
				while (j > 0)
					free(new_envp[--j]);
				return (free(new_envp), NULL);
			}
			j++;
		}
		i++;
	}
	return (new_envp);
}

static int	new_envp_var(t_context *ctx, char *var)
{
	int		size;
	char	**new_envp;
	char	**old_envp;

	size = 0;
	while (ctx->envp && ctx->envp[size])
		size++;
	new_envp = create_new_env_var(ctx->envp, var, size, 0);
	if (!new_envp)
		return (1);
	old_envp = ctx->envp;
	ctx->envp = new_envp;
	if (old_envp)
		free_cpy_envp(old_envp);
	return (0);
}

int	set_env_var(t_context *ctx, char *var)
{
	int		key_lenght;
	char	*key;
	int		index;

	key_lenght = ft_strchr(var, '=') - var;
	key = ft_substr(var, 0, key_lenght);
	if (!key)
		return (1);
	index = get_envp_index(key, ctx->envp);
	free(key);
	if (index != -1)
	{
		free(ctx->envp[index]);
		ctx->envp[index] = ft_strdup(var);
		if (!ctx->envp[index])
			return (1);
	}
	else
	{
		if (new_envp_var(ctx, var) != 0)
			return (1);
	}
	return (0);
}

int	unset_envp_var(t_context *ctx, char *key)
{
	int		index;
	int		env_size;
	char	**new_envp;
	char	**old_envp;

	index = get_envp_index(key, ctx->envp);
	if (index == -1)
		return (0);
	env_size = count_envp_vars(ctx->envp);
		new_envp = recreate_envp(ctx->envp, env_size, index);
	if (!new_envp)
		return (0);
	old_envp = ctx->envp;
	ctx->envp = new_envp;
	free_cpy_envp(old_envp);
	return (0);
}
