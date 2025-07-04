/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:53:19 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/03 23:31:39 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
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

char	*extract_quoted_token(char **input, char quote_char)
{
	char	*start;
	char	*result;
	int		len;

	start = *input;
	len = 1;
	(*input)++;
	while (**input && **input != quote_char)
	{
		(*input)++;
		len++;
	}
	if (**input == quote_char)
	{
		len++;
		(*input)++;
	}
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);
	return (result);
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
