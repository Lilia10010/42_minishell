/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:56:30 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/06 23:30:32 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
# include "parser.h"
#include "lib_ft.h"

t_command *create_command(void)
{
    t_command *cmd;
    
    cmd = (t_command *)malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    
    cmd->args = (char **)malloc(sizeof(char *) * 10); // Capacidade inicial
    if (!cmd->args)
    {
        free(cmd);
		int set_redirection(t_command *cmd, t_token *token, char *target);
        return (NULL);
    }
    
    cmd->arg_count = 0;
    cmd->arg_capacity = 10;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_mode = 0;
    cmd->heredoc_mode = 0;
    cmd->heredoc_delimiter = NULL;
    cmd->next = NULL;
    
    return (cmd);
}


void add_argument(t_command *cmd, char *arg)
{
    char **new_args;
    int new_capacity;
    
    if (!cmd || !arg)
        return;
    
    // Redimensionar array se necessário
    if (cmd->arg_count >= cmd->arg_capacity - 1) // -1 para NULL final
    {
        new_capacity = cmd->arg_capacity * 2;
        new_args = (char **)malloc(sizeof(char *) * new_capacity);
        if (!new_args)
        {
            printf("Error: memory allocation failed\n");
            return;
        }
        
        // Copiar argumentos existentes
        for (int i = 0; i < cmd->arg_count; i++)
            new_args[i] = cmd->args[i];
        
        free(cmd->args);
        cmd->args = new_args;
        cmd->arg_capacity = new_capacity;
    }
    
    // Adicionar novo argumento
    cmd->args[cmd->arg_count] = ft_strdup(arg);
    cmd->arg_count++;
    cmd->args[cmd->arg_count] = NULL; // Terminador NULL
}

int set_redirection(t_command *cmd, t_token *token, char *target)
{
    if (!cmd || !token || !target)
        return (0);
    
    if (token->type == TOKEN_REDIRECT_IN)
    {
        if (cmd->input_file)
            free(cmd->input_file);
        cmd->input_file = ft_strdup(target);
        cmd->heredoc_mode = 0;
    }
    else if (token->type == TOKEN_REDIRECT_OUT)
    {
        if (cmd->output_file)
            free(cmd->output_file);
        cmd->output_file = ft_strdup(target);
        cmd->append_mode = 0;
    }
    else if (token->type == TOKEN_REDIRECT_OUT_APPEND)
    {
        if (cmd->output_file)
            free(cmd->output_file);
        cmd->output_file = ft_strdup(target);
        cmd->append_mode = 1;
    }
    else if (token->type == TOKEN_HEREDOC)
    {
        if (cmd->heredoc_delimiter)
            free(cmd->heredoc_delimiter);
        cmd->heredoc_delimiter = ft_strdup(target);
        cmd->heredoc_mode = 1;
        // Limpar input_file se existir
        if (cmd->input_file)
        {
            free(cmd->input_file);
            cmd->input_file = NULL;
        }
    }
    
    return (1);
}