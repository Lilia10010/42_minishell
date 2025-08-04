/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:54:56 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/04 15:53:24 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
