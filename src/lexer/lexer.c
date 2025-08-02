/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:55:41 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/02 14:48:29 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "env.h"
#include "lib_ft.h"
#include "context_types.h"

static int	has_dollar(const char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}

static char *read_next_word_partial(char **current, t_context *ctx)
{
	char	*start;
	char	*word;
	char	*expanded;
	int		len;

	if (**current == '\'' || **current == '"')
		return (extract_quoted_token(current, **current, ctx));
	start = *current;
	len = 0;
	while (**current && **current != ' ' && **current != '\t' && !is_shell_operator(**current) && **current != '\'' && **current != '"')
	{
		(*current)++;
		len++;
	}
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	if (has_dollar(word))
	{
		expanded = expand_variables(word, ctx);
		free(word);
		return expanded;
	}
return word;
}

static int handle_word(t_token **tokens, char **current, t_context *ctx)
{
	char *word_value;
	char *partial;

	word_value = NULL;
	while (**current && !is_shell_operator(**current) && **current != ' ' && **current != '\t')
	{
		partial = read_next_word_partial(current, ctx);
		if (!partial)
			break;
		word_value = concatenate_strings(word_value, partial);
		free(partial);
		if (!word_value)
		{
			// ver qual o erro que deve ser retornado ou se apenas o break é suficiente
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

t_token *lexer_tokenize(char *input, t_context *ctx)
{
	t_token *tokens;
	char *current;

	tokens = NULL;
	current = input;
	while (*current)
	{
		skip_spaces(&current);
		if (!*current)
			break;
		if (is_shell_operator(*current))
		{
			if (!add_operator_token(&tokens, &current))
				break;
		}
		else
		{
			if (!handle_word(&tokens, &current, ctx))
				break;
		}
	}
	//debug_print_tokens(tokens);
	return (tokens);
}
