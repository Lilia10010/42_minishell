/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:00:22 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/13 11:42:45 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "command_types.h"

static void free_string_array(char **array)
{
	int i;

	i = 0;
    if (!array)
        return;
    while (array[i])
	{
        free(array[i++]);
		//printf("freeing: %s\n", array[i]);
	}
    free(array);
}

void free_command(t_command *cmd)
{
    if (!cmd)
        return;
    if (cmd->args)
    {
		free_string_array(cmd->args);
    }
    if (cmd->input_file)
        free(cmd->input_file);
    if (cmd->output_file)
    {
		free_string_array(cmd->output_file);
    }
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