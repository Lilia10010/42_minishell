/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:54:56 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/05 14:14:01 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "token_types.h"

int is_redirection_token(t_token_type type)
{
    return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT ||
            type == TOKEN_REDIRECT_OUT_APPEND || type == TOKEN_HEREDOC);
}

int validate_syntax(t_token *tokens)
{
    t_token *current;

	current = tokens;    
    if (!current)
        return (1);
    // Verificar se começa com pipe
    if (current->type == TOKEN_PIPE)
        return (0);
    while (current)
    {
        if (current->type == TOKEN_PIPE)
        {
            // Verificar se próximo token existe e não é pipe
            if (!current->next || current->next->type == TOKEN_PIPE)
                return (0);
        }
        if (is_redirection_token(current->type))
        {
            // Verificar se próximo token é WORD
            if (!current->next || current->next->type != TOKEN_WORD)
                return (0);
        }
        current = current->next;
    }
    // Verificar se termina com redirecionamento
    if (tokens)
    {
        // Encontrar último token
        current = tokens;
        while (current->next)
            current = current->next;
        
        if (is_redirection_token(current->type))
            return (0);
    }
    return (1);
}
char **remove_empty_args(char **args)
{
	int		i, j;
	char	**cleaned;

	if (!args)
		return (NULL);

	// Conta número de argumentos válidos
	int count = 0;
	for (i = 0; args[i]; i++)
		if (args[i][0] != '\0')
			count++;

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
			free(args[i]); // libera string vazia
		i++;
	}
	cleaned[j] = NULL;
	free(args); // libera array antigo (opcional)
	return cleaned;
}