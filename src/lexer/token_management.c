/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:17:08 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/14 15:28:21 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //para o printf caso não for usar RETIRAR
#include "lexer.h"
#include "lib_ft.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->value = NULL;
	return (token);
}

int	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return (0);
	if (!*head)
	{
		*head = new_token;
		return (1);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (1);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}

char	*concatenate_strings(char *str1, char *str2)
{
	char	*result;

	if (!str1)
		return (ft_strdup(str2));
	result = ft_strjoin(str1, str2);
	free(str1);
	return (result);
}
