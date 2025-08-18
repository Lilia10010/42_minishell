/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:11:47 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/18 08:37:08 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

static char  **create_envp(char **envp , int count)
{
	char	**new_envp;
	int		i;

	new_envp = ft_calloc(count + 2, sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i < 0)
				free(new_envp[i--]);
			return (free(new_envp), NULL);
		}
		i++;
	}
	return (new_envp);
}

static int	update_var(char **envp, int index, char *name, char *value)
{
	free(envp[index]);
	envp[index] = create_envp_string(name, value);
	if (!envp[index])
		return (-1);
	return (0);
}

static int	add_new_var(char **envp, char *name, char *value)
{
	char	**old_envp;
	char	**new_envp;
	int		count;

	count = count_envp_vars(envp);
	new_envp = create_envp(envp, count);
	if (!new_envp)
		return (-1);
	new_envp[count] = create_envp_string(name, value); 
	if (!new_envp[count])
	{
		free_cpy_envp(new_envp);
		return (-1);
	}
	old_envp = envp;
	envp = new_envp;
	free_cpy_envp(old_envp);
	return (0);
}

int	set_env(char **envp, char *name_var, char *value)
{
	int	check_var;
	
	if (check_envp_params(envp, name_var) == -1)
		return (-1);
	check_var = find_var(envp, name_var);
	if (check_var != -1)
		return (update_var(envp, check_var, name_var, value));
	return(add_new_var(envp, name_var, value));
}
