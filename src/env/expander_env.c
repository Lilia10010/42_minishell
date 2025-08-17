/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:57:42 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 19:49:03 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

static const char	*get_env_value(const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (__environ[i])
	{
		if (strncmp(__environ[i], key, key_len) == 0
			&& __environ[i][key_len] == '=')
			return (__environ[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

static char	*extract_var_name(const char **ptr)
{
	const char	*start;
	int			len;
	char		*var_name;

	start = *ptr;
	len = 0;
	while (**ptr && (ft_isalnum(**ptr) || **ptr == '-'))
	{
		(*ptr)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, start, len + 1);
	return (var_name);
}

static void	append_char(char **result, char c)
{
	char	temp[2];
	char	*old;

	temp[0] = c;
	temp[1] = '\0';
	old = *result;
	*result = ft_strjoin(*result, temp);
	free(old);
}

static void	append_to_result(char **result, const char *to_append)
{
	char	*old;

	old = *result;
	*result = ft_strjoin(*result, to_append);
	free(old);
}

static void	handle_variable_expansio(char **result, const char **ptr,
	t_context *ctx)
{
	char		*var_name;
	const char	*value;
	char		*exit_code_str;

	if (**ptr == '?')
	{
		exit_code_str = ft_itoa(ctx->exit_status);
		append_to_result(result, exit_code_str);
		free(exit_code_str);
		(*ptr)++;
		return ;
	}
	var_name = extract_var_name(ptr);
	if (!var_name)
		return ;
	value = get_env_value(var_name);
	if (value)
		append_to_result(result, value);
	free(var_name);
}

static void	handle_tilde_expansion(char **result, const char **ptr)
{
    const char	*home;
    
    home = get_env_value("HOME");
    if (home)
        append_to_result(result, home);
    else
        append_to_result(result, "~");
    (*ptr)++; 
}

char	*expand_variables(const char *input, t_context *ctx)
{
	char		*result;
	const char	*ptr;
	char		temp[2];

	result = ft_strdup("");
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '$')
		{
			ptr++;
			handle_variable_expansio(&result, &ptr, ctx);
		}
		else if (*ptr == '~')
		{
			handle_tilde_expansion(&result, &ptr);			
		}
		else
		{
			temp[0] = *ptr;
			temp[1] = '\0';
			append_char(&result, *temp);
			ptr++;
		}
	}
	return (result);
}
