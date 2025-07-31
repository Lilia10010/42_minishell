/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:00:22 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/31 00:33:16 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "command_types.h"

void free_command(t_command *cmd)
{
    int i;
    
    if (!cmd)
        return;
    
    // Liberar argumentos
    if (cmd->args)
    {
        for (i = 0; i < cmd->arg_count; i++)
        {
            if (cmd->args[i])
                free(cmd->args[i]);
        }
        free(cmd->args);
    }
    
    // Liberar arquivos de redirecionamento
    if (cmd->input_file)
        free(cmd->input_file);
    if (cmd->output_file)
        free(cmd->output_file);
    if (cmd->heredoc_delimiter)
        free(cmd->heredoc_delimiter);
    
    free(cmd);
}

void free_commands(t_command *commands)
{
    t_command *current;
    t_command *next;
    
    current = commands;
    while (current)
    {
        next = current->next;
        free_command(current);
        current = next;
    }
}
