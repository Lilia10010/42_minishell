/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:53:19 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/02 14:48:40 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "env.h"
#include "lib_ft.h"

void	skip_spaces(char **input)
{
	while (**input == ' ' || **input == '\t')
		(*input)++;
}

int	is_shell_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char *extract_quoted_token(char **input, char quote_char, t_context *ctx)
{
	char *start;
	char *raw;
	char *final;
	int len;

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
	{
		final = expand_variables(raw, ctx);
		free(raw);
		return (final);
	}
}

static int	handle_redirect_in_operators(t_token **tokens, char **current)
{
	if (*(*current +1) == '<')
	{
		add_token(tokens, create_token(TOKEN_HEREDOC, ft_strdup("<<")));
		(*current) += 2;
		return (1);
	}
	else
	{
		add_token(tokens, create_token(TOKEN_REDIRECT_IN, ft_strdup("<")));
		(*current)++;
		return (1);
	}
}

int	add_operator_token(t_token **tokens, char **current)
{
	if (**current == '|' )
	{
		add_token(tokens, create_token(TOKEN_PIPE, ft_strdup("|")));
		(*current)++;
		return (1);
	}
	else if (**current == '>' && *(*current + 1) == '>')
	{
		add_token(tokens,
			create_token(TOKEN_REDIRECT_OUT_APPEND, ft_strdup(">>")));
		(*current) += 2;
		return (1);
	}
	else if (**current == '>')
	{
		add_token(tokens, create_token(TOKEN_REDIRECT_OUT, ft_strdup(">")));
		(*current)++;
		return (1);
	}
	else if (**current == '<')
		return (handle_redirect_in_operators(tokens, current));
	return (0);
}
