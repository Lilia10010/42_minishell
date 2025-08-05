/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:00:22 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/05 18:54:57 by microbiana       ###   ########.fr       */
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

    // Free arguments
    if (cmd->args)
    {
        for (i = 0; i < cmd->arg_count; i++)
        {
            if (cmd->args[i])
                free(cmd->args[i]);
        }
        free(cmd->args);
    }

    // Free input file
    if (cmd->input_file)
        free(cmd->input_file);

    // Free output files
    if (cmd->output_file)
    {
        for (i = 0; i < cmd->output_file_count; i++)
        {
            if (cmd->output_file[i])
                free(cmd->output_file[i]);
        }
        free(cmd->output_file);
    }

    free(cmd); // Free the command structure itself
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