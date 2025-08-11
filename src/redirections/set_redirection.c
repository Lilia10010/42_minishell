/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:39:21 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/10 23:49:55 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "command_types.h"
#include "lib_ft.h"
#include "token_types.h"

static void set_input_file(t_command *cmd, char *target)
{
	if (cmd->input_file)
		free(cmd->input_file);
	cmd->input_file = ft_strdup(target);
	cmd->heredoc_mode = 0;//ára desatovar o mode heredoc
}

static int expand_output_file_array(t_command *cmd)
{
	char **new_array;
	int new_capacity;
	int i;

	new_capacity = cmd->output_file_count + 10;
	new_array = (char **)malloc(sizeof(char *) * new_capacity);
	if (!new_array)
		return (0);
	i = 0;
	while (i < cmd->output_file_count)
	{
		new_array[i] = cmd->output_file[i];
		i++;
	}
	free(cmd->output_file);
	cmd->output_file = new_array;
	return (1);
}

static void set_output_file(t_command *cmd, char *target, int append_mode)
{
	char *dup_target;

	if (!cmd || !target)
		return;

	// Expande se necessário
	if (cmd->output_file_count % 10 == 0)
	{
		if (!expand_output_file_array(cmd))
		{
			perror("Error: expanding output file array");
			return;
		}
	}

	// Duplica o nome do arquivo
	dup_target = ft_strdup(target);
	if (!dup_target)
	{
		perror("Error duplicating output filename");
		return;
	}

	cmd->output_file[cmd->output_file_count++] = dup_target;
	cmd->output_file[cmd->output_file_count] = NULL; // garante NULL termination

	cmd->append_mode = append_mode; // 0 = truncate (>), 1 = append (>>)
}

static void set_heredoc(t_command *cmd, char *target)
{
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	cmd->heredoc_delimiter = ft_strdup(target);
	cmd->heredoc_mode = 1;
	if (cmd->input_file)
	{
		free(cmd->input_file);
		cmd->input_file = NULL;
	}
}
//parametros: comando - token - e o alvo arquivo de destino ou delimitador
int	set_redirection(t_command *cmd, t_token *token, char *target)
{
	if (!cmd || !token || !target)
		return (0);
	if (token->type == TOKEN_REDIRECT_IN)
		set_input_file(cmd, target);
	else if (token->type == TOKEN_REDIRECT_OUT)
		set_output_file(cmd, target, 0);
	else if (token->type == TOKEN_REDIRECT_OUT_APPEND)
		set_output_file(cmd, target, 1);
	else if (token->type == TOKEN_HEREDOC)
		set_heredoc(cmd, target);
	return (1);
}