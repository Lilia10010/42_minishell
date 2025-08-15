/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:54:56 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/11 17:07:07 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "token_types.h"

int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_OUT_APPEND || type == TOKEN_HEREDOC);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!current)
		return (1);
	if (current->type == TOKEN_PIPE)
		return (0);
	while (current)
	{
		if (current->type == TOKEN_PIPE && (!current->next || current->next->type == TOKEN_PIPE))
			return (0);
		if (is_redirection_token(current->type) && (!current->next || current->next->type != TOKEN_WORD))
			return (0);
		current = current->next;
	}
	current = tokens;
	while (current && current->next)
		current = current->next;
	if (current && is_redirection_token(current->type))
		return (0);
	return (1);
}

static int	count_valid_args(char **args)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (args[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

char	**remove_empty_args(char **args)
{
	int		i;
	int		j;
	int		count;
	char	**cleaned;

	count = count_valid_args(args);
	cleaned = malloc(sizeof(char *) * (count + 1));
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			cleaned[j++] = args[i];
		else
			free(args[i]);
		i++;
	}
	cleaned[j] = NULL;
	free(args);
	return (cleaned);
}
