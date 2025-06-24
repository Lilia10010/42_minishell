/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:55:41 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/23 23:09:31 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ft.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void	skip_spaces(char **input)
{
	while (**input == ' ' || **input == '\t')
		(*input)++;
}

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	handle_operator(t_token **tokens, char **current)
{
	if (**current == '|' )
	{
		add_token(tokens, create_token(TOKEN_PIPE, ft_strdup("|")));
		(*current)++;
	}
	else if (**current == '>' && *(*current + 1) == '>')
	{
		add_token(tokens, create_token(TOKEN_REDIRECT_OUT_APPEND, ft_strdup(">>")));
		(*current) += 2;
	}
	else if (**current == '>')
	{
		add_token(tokens, create_token(TOKEN_REDIRECT_OUT, ft_strdup(">")));
		(*current)++;
	}
	else if (**current == '<' && *(*current + 1) == '<')
	{
		add_token(tokens, create_token(TOKEN_HEREDOC, ft_strdup("<<")));
		(*current) += 2;
	}
	else if (**current == '<')
	{
		add_token(tokens, create_token(TOKEN_REDIRECT_IN, ft_strdup("<")));
		(*current)++;
	}
}

static void	handle_word(t_token **tokens, char **current)
{
	char	*start;
	int		len;
	char	*word;

	start = *current;
	len = 0;
	while (**current && !is_operator(**current) && **current != ' ' && **current != '\t')
	{
		(*current)++;
		len++;
	}
	word = malloc(len + 1);
	if (!word)
		return ;
	strncpy(word, start, len);
	word[len] = '\0';
	add_token(tokens, create_token(TOKEN_WORD, word));
	free(word);
}

t_token	*lexer_tokenize(char *input)
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
		if (is_operator(*current))
			handle_operator(&tokens, &current);
		else
			handle_word(&tokens, &current);
	}
	// Debug
	t_token *tmp = tokens;
	int i = 0;
	while (tmp)
	{
		printf(" DEBUGZIM Token %d: tipo= %d, valor= '%s'\n",
			i++, tmp->type, tmp->value);
		tmp = tmp->next;
	}
	return (tokens);
}
