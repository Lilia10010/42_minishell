/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:00:22 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/04 16:47:51 by microbiana       ###   ########.fr       */
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

	 // Free output files
    if (cmd->output_file)
{
    for (i = 0; i < cmd->output_file_count; i++)
    {
        if (cmd->output_file[i])
		{
            free(cmd->output_file[i]); // Free each filename
			cmd->output_file[i] = NULL; // Set to NULL to avoid dangling pointers
		}

    }
    //free(cmd->output_file); // Free the array itself
}
    
    // Liberar arquivos de redirecionamento
    if (cmd->input_file)
        free(cmd->input_file);
   /*  if (cmd->output_file)
        free(cmd->output_file); */
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
