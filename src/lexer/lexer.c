/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:55:41 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/01 23:59:01 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

static char	*extract_quoted_string(char **input, char quote_char)
{
	printf("input quoted %s\n", *input);

	char	*start;
	char	*result;
	int		len;

	(*input)++;

	start = *input;
	len = 0;

	while (**input && **input != quote_char)
	{
		(*input)++;
		len++;
	}

	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);

	if (**input == quote_char)
		(*input)++;
	return (result);
}



static char *read_next_word_partial(char **current)
{
	char	*start;
	char	*word;
	int		len;

	if (**current == '\'' || **current == '"')
		return (extract_quoted_string(current, **current));
	
	start = *current;
	len = 0;

	while (**current && **current != ' ' && **current != '\t'
		&& !is_operator(**current) && **current != '\'' && **current != '"')
	{
		(*current)++;
		len++;
	}

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
	 
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
	char	*value;
	char 	*partial;
	char	*temp;

	value = NULL;
	while (**current && !is_operator(**current) && **current != ' ' && **current != '\t')
	{
		partial = read_next_word_partial(current);
		if (!partial)
			break ;

		temp = value;
		if (value)
			value = ft_strjoin(value, partial);
		else
			value = ft_strdup(partial);
		free(partial);
		
		if (temp)
			free(temp);
		if (!value)
		{
			fprintf(stderr, "Error allocating memory for token value\n");
			//ver qual o erro que deve ser retornado ou se apenas o break é suficiente
			break ;
		}
	}
	
	if (value)
	{
		add_token(tokens, create_token(TOKEN_WORD, value));
		free(value);
	}
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
		printf(" DEBUGZIM Token %d: tipo= %d, valor=%s\n",
			i++, tmp->type, tmp->value);
		tmp = tmp->next;
	}
	return (tokens);
}
