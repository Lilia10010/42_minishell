/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_state.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:02:54 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/20 20:05:57 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "command_types.h"
#include "lib_ft.h"

static int	start_new_command(t_command **commands, t_command **current,
	t_command **last)
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

int	handle_expecting_command(t_token *token, t_parser_context *ctx)
{
	if (!start_new_command(ctx->commands, ctx->current_cmd, ctx->last_cmd))
		return (-1);
	if (!add_argument(*ctx->current_cmd, token->value))
		return (-1);
	*ctx->state = EXPECTING_ARGS;
	return (1);
}

int	handle_expecting_heredoc(t_token *token, t_parser_context *ctx)
{
	(*ctx->current_cmd)->heredoc_delimiter = ft_strdup(token->value);
	if (!(*ctx->current_cmd)->heredoc_delimiter)
		return (-1);
	(*ctx->current_cmd)->heredoc_mode = 1;
	*ctx->state = EXPECTING_ARGS;
	return (1);
}

void	cleanup_commands(t_command *commands)
{
	t_command	*cmd_iter;

	cmd_iter = commands;
	while (cmd_iter)
	{
		cmd_iter->args = remove_empty_args(cmd_iter->args);
		cmd_iter = cmd_iter->next;
	}
}
