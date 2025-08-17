/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:02:31 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 19:26:02 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "lib_ft.h"
#include "parser.h"
#include "command_types.h"
#include "context_types.h"

static int	process_tokens_loop(t_token *tokens, t_parser_context *ctx)
{
	t_token	*current_token;
	int		consumed;

	current_token = tokens;
	while (current_token)
	{
		consumed = handle_token(current_token, ctx);
		if (consumed < 0)
			return (-1);
		while (consumed > 0 && current_token)
		{
			current_token = current_token->next;
			consumed--;
		}
	}
	return (0);
}

static t_command	*build_command_list(t_token *tokens)
{
	t_parser_context	ctx;
	t_command			*commands;
	t_command			*current_cmd;
	t_command			*last_cmd;
	t_parser_state		state;

	commands = NULL;
	current_cmd = NULL;
	last_cmd = NULL;
	state = EXPECTING_COMMAND;
	ctx = (t_parser_context){&state, &current_cmd, &commands, &last_cmd};
	if (process_tokens_loop(tokens, &ctx) < 0)
	{
		free_commands(commands);
		return (NULL);
	}
	cleanup_commands(commands);
	return (commands);
}

t_command	*parse_tokens(t_token *tokens, t_context *ctx)
{
	if (!tokens)
		return (NULL);
	if (!validate_syntax(tokens))
	{
		printf("bash: syntax error near unexpected token: `%s'\n", tokens->value);
		ctx->exit_status = 2;
		return (NULL);
	}
	return (build_command_list(tokens));
}
