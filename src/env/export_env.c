/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:58:39 by meandrad          #+#    #+#             */
/*   Updated: 2025/08/18 08:42:32 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

static void	export_format(char *env_var)
{
	char	*equal_sing;

	equal_sing = ft_strchr(env_var, '=');
	if (equal_sing)
	{
		*equal_sing = '\0';
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(equal_sing + 1, 1);
		ft_putstr_fd("\"\n", 1);
		*equal_sing = '=';
	}
	else
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("\n", 1);
	}
}

static int	compare_vars(char *s1, char *s2)
{
	int	lenght1;
	int	lenght2;
	int	min_lenght;

	lenght1 = ft_strlen(s1);
	lenght2 = ft_strlen(s2);
	min_lenght = lenght1;
	if (lenght2 < lenght1)
		min_lenght = lenght2;
	return (ft_strncmp(s1, s2, min_lenght + 1));
}

static void	sort_envp(char **env_copy, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (compare_vars(env_copy[j], env_copy[j + 1]) > 0)
			{
				temp = env_copy[j];
				env_copy[j] = env_copy[j + 1];
				env_copy[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	**cpy_envp_sort(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;

	count = count_envp_vars(envp);
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			free_cpy_envp(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

void	sorted_envp(char **envp)
{
	char	**envp_cpy;
	int		count;
	int		i;

	if (!envp)
		return ;
	envp_cpy = cpy_envp_sort(envp);
	if (!envp_cpy)
		return ;
	count = count_envp_vars(envp_cpy);
	sort_envp(envp_cpy, count);
	i = 0;
	while (envp_cpy[i])
	{
		export_format(envp_cpy[i]);
		i++;
	}
	free_cpy_envp(envp_cpy);
}
