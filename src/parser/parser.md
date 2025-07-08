/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:52:16 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/06 19:07:32 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>

# include "parser.h"
# include "minishell.h"
#include <stdio.h> //para o printf caso não for usar RETIRAR

t_command *parse_tokens(t_token *tokens)
{
    t_command *commands = NULL;
    t_command *current_cmd = NULL;
    t_command *last_cmd = NULL;
    t_token *current_token = tokens;
    t_parser_state state = EXPECTING_COMMAND;
    
    // Validação sintática inicial
    if (!validate_syntax(tokens))
    {
        printf("Syntax error\n");
        return (NULL);
    }
    
    // Processar tokens sequencialmente
    while (current_token)
    {
        if (current_token->type == TOKEN_WORD)
        {
            if (state == EXPECTING_COMMAND)
            {
                // Criar novo comando
                current_cmd = create_command();
                if (!current_cmd)
                {
                    free_commands(commands);
                    return (NULL);
                }
                
                // Adicionar à lista de comandos
                if (!commands)
                    commands = current_cmd;
                else
                    last_cmd->next = current_cmd;
                last_cmd = current_cmd;
                
                add_argument(current_cmd, current_token->value);
                state = EXPECTING_ARGS;
            }
            else if (state == EXPECTING_ARGS)
            {
                // Adicionar argumento ao comando atual
                add_argument(current_cmd, current_token->value);
            }
            else if (state == EXPECTING_REDIRECT_TARGET)
            {
                // Este caso já é tratado no bloco de redirecionamento
                // Não deveria chegar aqui se a lógica estiver correta
                state = EXPECTING_ARGS;
            }
            else if (state == EXPECTING_HEREDOC_DELIMITER)
            {
                // Configurar heredoc
                current_cmd->heredoc_delimiter = ft_strdup(current_token->value);
                current_cmd->heredoc_mode = 1;
                state = EXPECTING_ARGS;
            }
        }
        else if (is_redirection_token(current_token->type))
        {
            if (!current_cmd)
            {
                printf("Syntax error: redirection without command\n");
                free_commands(commands);
                return (NULL);
            }
            
            // Processar redirecionamento
            t_token *next_token = current_token->next;
            if (!next_token || next_token->type != TOKEN_WORD)
            {
                printf("Syntax error: redirection without target\n");
                free_commands(commands);
                return (NULL);
            }
            
            if (!set_redirection(current_cmd, current_token, next_token->value))
            {
                free_commands(commands);
                return (NULL);
            }
            
            // Pular o próximo token (já processado)
            current_token = next_token;
            state = EXPECTING_ARGS; // Voltar ao estado de espera de argumentos
        }
        else if (current_token->type == TOKEN_PIPE)
        {
            if (!current_cmd)
            {
                printf("Syntax error: pipe without command\n");
                free_commands(commands);
                return (NULL);
            }
            state = EXPECTING_COMMAND;
        }
        
        current_token = current_token->next;
    }
    
    return (commands);
}
