/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:57:42 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/19 10:46:06 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

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
	value = get_env_value(var_name, ctx);
	if (value)
		append_to_result(result, value);
	free(var_name);
}

static void	handle_tilde_expansion(char **result, const char **ptr,
	t_context *ctx)
{
	const char	*home;

	(*ptr)++;
	home = get_env_value("HOME", ctx);
	if (home)
		append_to_result(result, home);
	else
		append_to_result(result, "~");
	(*ptr)++;
}

static void	handle_char(char c, char **result)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	append_char(result, *temp);
}

char	*expand_variables(const char *input, t_context *ctx)
{
	char		*result;
	const char	*ptr;

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
			handle_tilde_expansion(&result, &ptr, ctx);
		else
			handle_char(*ptr++, &result);
	}
	return (result);
}
