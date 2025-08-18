/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:57:42 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/16 12:21:27 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

static const char *get_env_value2(const char *key, t_context *ctx)
{
	size_t	i;
	size_t	key_len;

	if (!key || !ctx || !ctx->envp)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (ctx->envp[i])
	{
		if (ft_strncmp(ctx->envp[i], key, key_len) == 0 && ctx->envp[i][key_len] == '=')
			return (ctx->envp[i] + key_len + 1);
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
	while (**ptr && (ft_isalnum(**ptr) || **ptr == '-'))//ou _ 
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
	value = get_env_value2(var_name, ctx);
	if (value)
		append_to_result(result, value);
	free(var_name);
}

static void	handle_tilde_expansion(char **result, const char **ptr, t_context *ctx)
{
    const char	*home;
    
	home = get_env_value2("HOME", ctx);
    if (home)
        append_to_result(result, home);
    else
        append_to_result(result, "~");
    (*ptr)++; 
}

/* static void debug_envp(char **envp)
{
    int i = 0;

    if (!envp)
    {
        printf("ctx->envp is NULL\n");
        return;
    }

    printf("Environment Variables (ctx->envp):\n");
    while (envp[i])
    {
        printf("[%d]: %s\n", i, envp[i]);
        i++;
    }
    printf("Total variables: %d\n", i);
} */

char	*expand_variables(const char *input, t_context *ctx)
{
	char		*result;
	const char	*ptr;
	char		temp[2];

//	debug_envp(ctx->envp);

	if (!input)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
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
			handle_tilde_expansion(&result, &ptr, ctx);			
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
