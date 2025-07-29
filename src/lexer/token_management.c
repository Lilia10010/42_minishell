/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:17:08 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/29 00:22:11 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lib_ft.h"
#include <stdio.h> //para o printf caso não for usar RETIRAR

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

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

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
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

void	debug_print_tokens(t_token *tokens)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens;
	printf("\n=== TOKENS DEBUG ===\n");
	while (current)
	{
		printf("Token %d: tipo=%d, valor=%s\n",
			i++, current->type, current->value);
		current = current->next;
	}
	printf("===================\n");
}
