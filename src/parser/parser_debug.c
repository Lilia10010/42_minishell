/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:01:21 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/05 14:07:51 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include "command_types.h"

void debug_print_commands(t_command *commands)
{
    t_command *current;
    int cmd_num;
    int i;
    
    current = commands;
    cmd_num = 0;
    
    printf("\n=== COMMANDS DEBUG ===\n");
    while (current)
    {
        printf("Command %d:\n", cmd_num++);
        printf("  Args (%d): ", current->arg_count);
        if (current->args)
        {
            for (i = 0; i < current->arg_count; i++)
                printf("[%s] ", current->args[i]);
        }
        printf("\n");
        
        if (current->input_file)
            printf("  Input: %s\n", current->input_file);
        if (current->output_file)
{
    printf("  Output: ");
    for (int j = 0; current->output_file[j]; j++)
        printf("%s ", current->output_file[j]);
    printf("(%s)\n", current->append_mode ? "append" : "overwrite");
}
        if (current->heredoc_mode && current->heredoc_delimiter)
            printf("  Heredoc delimiter: %s\n", current->heredoc_delimiter);
        
        current = current->next;
        if (current)
            printf("  | (pipe to next command)\n");
    }
    printf("======================\n");
}