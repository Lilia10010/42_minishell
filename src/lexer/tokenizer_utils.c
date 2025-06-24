/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:17:08 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/23 22:18:23 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>
#include "lib_ft.h"

t_token *create_token(t_token_type type, char *value)
{
    t_token *token;

	token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    
    token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;

    token->next = NULL;
    return (token);
}

void add_token(t_token **head, t_token *new_token)
{
	t_token *current;

    if (!*head)
    {
        *head = new_token;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

void free_tokens(t_token *tokens)
{
	t_token *current;
	t_token *next;

	current = tokens;

	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
