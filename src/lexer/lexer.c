/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:55:41 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 19:49:42 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

int	has_expandable_dollar(const char *str)
{
	int		i;
	char	next;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			next = str[i + 1];
			if (next == '\0' || next == ' ' || next == '\t'
				|| !(ft_isalnum(next) || next == '_' || next == '?'))
			{
				i++;
				continue ;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int has_tilde_expansion(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '~')
		{
			if (str[i + 1] == '\0' || str[i + 1] == ' '
				|| str[i + 1] == '\t' || str[i + 1] == '/')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	count_word_length(char **current)
{
	int	len;

	len = 0;
	while (**current && **current != ' ' && **current != '\t'
		&& !is_shell_operator(**current)
		&& **current != '\'' && **current != '"')
	{
		(*current)++;
		len++;
	}
	return (len);
}

static char	*read_next_word_partial(char **current, t_context *ctx)
{
	char	*start;
	char	*word;
	char	*expanded;
	int		len;

	if (**current == '\'' || **current == '"')
		return (extract_quoted_token(current, **current, ctx));
	start = *current;
	len = count_word_length(current);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	if (has_expandable_dollar(word) || has_tilde_expansion(word))
	{
		expanded = expand_variables(word, ctx);
		free(word);
		return (expanded);
	}
	return (word);
}

static int	handle_word(t_token **tokens, char **current, t_context *ctx)
{
	char	*word_value;
	char	*partial;

	word_value = NULL;
	while (**current && !is_shell_operator(**current)
		&& **current != ' ' && **current != '\t')
	{
		partial = read_next_word_partial(current, ctx);
		if (!partial)
			break ;
		word_value = concatenate_strings(word_value, partial);
		free(partial);
		if (!word_value)
		{
			printf("Error allocating memory for token word_value\n");
			return (0);
		}
	}
	if (word_value)
	{
		add_token(tokens, create_token(TOKEN_WORD, word_value));
		free(word_value);
		return (1);
	}
	return (0);
}

t_token	*lexer_tokenize(char *input, t_context *ctx)
{
	t_token	*tokens;
	char	*current;

	tokens = NULL;
	current = input;
	while (*current)
	{
		skip_spaces(&current);
		if (!*current)
			break ;
		if (is_shell_operator(*current))
		{
			if (!add_operator_token(&tokens, &current))
				break ;
		}
		else
		{
			if (!handle_word(&tokens, &current, ctx))
				break ;
		}
	}
	return (tokens);
}
