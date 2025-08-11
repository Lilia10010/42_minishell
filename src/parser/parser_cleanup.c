/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:00:22 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/11 13:43:21 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "command_types.h"

static void free_string_array(char **array, int count)
{
	int i;

	i = 0;
	if (!array)
		return;
	while (i < count)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

void free_command(t_command *cmd)
{
    if (!cmd)
        return;
    if (cmd->args)
    {
		free_string_array(cmd->args, cmd->arg_count);
    }
    if (cmd->input_file)
        free(cmd->input_file);
    if (cmd->output_file)
    {
		free_string_array(cmd->output_file, cmd->output_file_count);
    }
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