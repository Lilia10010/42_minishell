/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:39:21 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/14 00:20:15 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "parser.h"
#include "lexer.h"
#include "lib_ft.h"


static void set_input_file(t_command *cmd, char *target)
{
	if (cmd->input_file)
		free(cmd->input_file);
	cmd->input_file = ft_strdup(target);
	cmd->heredoc_mode = 0;//ára desatovar o mode heredoc
}

static void set_output_file(t_command *cmd, char *target, int append)
{
	if (cmd->output_file)
		free(cmd->output_file);
	cmd->output_file = ft_strdup(target);
	cmd->append_mode = append;//0 para >, 1 para >>
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
//parametros: comando - token - e o alvo
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