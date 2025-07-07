/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:02:31 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/06 23:37:04 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

// Função auxiliar: inicializa novo comando e conecta à lista
static int start_new_command(t_command **commands, t_command **current, t_command **last)
{
    *current = create_command();
    if (!*current)
        return (0);
    
    if (!*commands)
        *commands = *current;
    else
        (*last)->next = *current;
    
    *last = *current;
    return (1);
}

// Função auxiliar: processa redirecionamento
static int handle_redirection(t_token **token, t_command *cmd, t_command *commands)
{
    t_token *redir = *token;
    t_token *target = redir->next;

    if (!cmd)
    {
        printf("Syntax error: redirection without command\n");
        free_commands(commands);
        return (0);
    }

    if (!target || target->type != TOKEN_WORD)
    {
        printf("Syntax error: redirection without target\n");
        free_commands(commands);
        return (0);
    }

    if (!set_redirection(cmd, redir, target->value))
    {
        free_commands(commands);
        return (0);
    }

    *token = target; // Avança, já que redirecionamento usa dois tokens
    return (1);
}

// Função auxiliar: processa token do tipo WORD
static void handle_word_token(t_token *token, t_parser_state *state, t_command **cmd, t_command **cmds, t_command **last)
{
    if (*state == EXPECTING_COMMAND)
    {
        if (!start_new_command(cmds, cmd, last))
        {
            free_commands(*cmds);
            *cmds = NULL;
            return;
        }
        add_argument(*cmd, token->value);
        *state = EXPECTING_ARGS;
    }
    else if (*state == EXPECTING_ARGS)
    {
        add_argument(*cmd, token->value);
    }
    else if (*state == EXPECTING_HEREDOC_DELIMITER)
    {
        (*cmd)->heredoc_delimiter = ft_strdup(token->value);
        (*cmd)->heredoc_mode = 1;
        *state = EXPECTING_ARGS;
    }
}

// Função auxiliar: processa pipe
static int handle_pipe_token(t_command *cmd, t_command *commands)
{
    if (!cmd)
    {
        printf("Syntax error: pipe without command\n");
        free_commands(commands);
        return (0);
    }
    return (1);
}

// Função principal refatorada
t_command *parse_tokens(t_token *tokens)
{
    t_command *commands = NULL;
    t_command *current_cmd = NULL;
    t_command *last_cmd = NULL;
    t_token *current_token = tokens;
    t_parser_state state = EXPECTING_COMMAND;

    if (!validate_syntax(tokens))
    {
        printf("Syntax error\n");
        return (NULL);
    }
    while (current_token)
    {
        if (current_token->type == TOKEN_WORD)
        {
            handle_word_token(current_token, &state, &current_cmd, &commands, &last_cmd);
        }
        else if (is_redirection_token(current_token->type))
        {
            if (!handle_redirection(&current_token, current_cmd, commands))
                return (NULL);
        }
        else if (current_token->type == TOKEN_PIPE)
        {
            if (!handle_pipe_token(current_cmd, commands))
                return (NULL);
            state = EXPECTING_COMMAND;
        }
        current_token = current_token->next;
    }
    return commands;
}
