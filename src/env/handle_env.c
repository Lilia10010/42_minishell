/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:47:35 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/18 20:27:18 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

char	*get_env_value(const char *key, t_context *ctx)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (ctx->envp[i])
	{
		if (ft_strncmp(ctx->envp[i], key, key_len) == 0
			&& ctx->envp[i][key_len] == '=')
			return (ctx->envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	find_var(char **envp, char *name)
{
	int	lenght_var;
	int	i;
	
	lenght_var = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, lenght_var) == 0 
			&& envp[i][lenght_var] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*create_envp_string(char *name, char *value)
{
	char	*temp;
	char	*result;
	
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}