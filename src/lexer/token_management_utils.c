/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:53:19 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/15 14:30:58 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "env.h"
#include "lib_ft.h"

static char	*handle_double_quote_expansion(char *raw, t_context *ctx)
{
	char	*end;

	if (!has_expandable_dollar(raw))
		return (raw);
	end = expand_variables(raw, ctx);
	free(raw);
	return (end);
}

char	*extract_quoted_token(char **input, char quote_char, t_context *ctx)
{
	char	*start;
	char	*raw;
	int		len;

	(*input)++;
	start = *input;
	len = 0;
	while (**input && **input != quote_char)
	{
		(*input)++;
		len++;
	}
	raw = (char *)malloc(len + 1);
	if (!raw)
		return (NULL);
	ft_strlcpy(raw, start, len + 1);
	if (**input == quote_char)
		(*input)++;
	if (quote_char == '\'')
		return (raw);
	else
		return (handle_double_quote_expansion(raw, ctx));
}

int	create_and_add_token(t_token **tokens,
	t_token_type type, char *value)
{
	t_token	*token;

	token = create_token(type, value);
	if (!token)
		return (0);
	if (!add_token(tokens, token))
	{
		free_token(token);
		return (0);
	}
	return (1);
}

static int	handle_redirect_in_operators(t_token **tokens, char **current)
{
	if (*(*current + 1) == '<')
	{
		if (!create_and_add_token(tokens, TOKEN_HEREDOC, "<<"))
			return (0);
		(*current) += 2;
		return (1);
	}
	else
	{
		if (!create_and_add_token(tokens, TOKEN_REDIRECT_IN, "<"))
			return (0);
		(*current)++;
		return (1);
	}
}

int	add_operator_token(t_token **tokens, char **current)
{
	if (**current == '|')
	{
		if (!try_add_token(tokens, TOKEN_PIPE, "|"))
			return (0);
		(*current)++;
		return (1);
	}
	else if (**current == '>')
		return (handle_redirect_out_operator(tokens, current));
	else if (**current == '<')
		return (handle_redirect_in_operators(tokens, current));
	return (0);
}
