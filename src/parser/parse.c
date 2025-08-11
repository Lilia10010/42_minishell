/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:02:31 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/11 16:47:38 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "redirection.h"
#include "lib_ft.h"
#include "parser.h"
#include "command_types.h"

static int start_new_command(t_command **commands, t_command **current, t_command **last)
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

static int handle_redirection(t_token *token, t_command *cmd)
{
	t_token *target;

	target = token->next;
	if (!cmd)
	{
		printf("Syntax error: redirection without command\n");
		return (-1);
	}
	if (!target || target->type != TOKEN_WORD)
	{
		printf("Syntax error: redirection without target\n");
		return (-1);
	}
	if (!set_redirection(cmd, token, target->value))
	{
		return (-1);
	}
	return (2); // consumiu 2 tokens: redirection e target
}

static int handle_word_token(t_token *token, t_parser_state *state, t_command **cmd, t_command **cmds, t_command **last)
{
	if (*state == EXPECTING_COMMAND)
	{
		if (!start_new_command(cmds, cmd, last))
			return (-1);
		if (!add_argument(*cmd, token->value))
			return (-1);
		*state = EXPECTING_ARGS;
	}
	else if (*state == EXPECTING_ARGS)
	{
		if (!add_argument(*cmd, token->value))
			return (-1);
	}
	else if (*state == EXPECTING_HEREDOC_DELIMITER)
	{
		(*cmd)->heredoc_delimiter = ft_strdup(token->value);
		if (!(*cmd)->heredoc_delimiter)
			return (-1);
		(*cmd)->heredoc_mode = 1;
		*state = EXPECTING_ARGS;
	}
	return (1);
}

static int handle_pipe_token(t_command *cmd, t_parser_state *state)
{
	if (!cmd)
	{
		printf("Syntax error: pipe without command\n");
		return (-1);
	}
	*state = EXPECTING_COMMAND;
	return (1);
}

static int handle_token(t_token *token, t_parser_state *state, t_command **current_cmd, t_command **commands, t_command **last_cmd)
{
	int consumed;

	if (token->type == TOKEN_WORD)
		consumed = handle_word_token(token, state, current_cmd, commands, last_cmd);
	else if (is_redirection_token(token->type))
		consumed = handle_redirection(token, *current_cmd);
	else if (token->type == TOKEN_PIPE)
		consumed = handle_pipe_token(*current_cmd, state);
	else if (token->type == TOKEN_HEREDOC)
	{
		*state = EXPECTING_HEREDOC_DELIMITER;
		consumed = 1;
	}
	else
	{
		printf("Unknown token type: %d\n", token->type);
		consumed = -1;
	}
	return (consumed);
}

static t_command *build_command_list(t_token *tokens)
{
	t_command		*commands, *current_cmd, *last_cmd;
	t_token			*current_token;
	t_parser_state	state;
	t_command		*cmd_iter;
	int				consumed;

	commands = NULL;
	current_cmd = NULL;
	last_cmd = NULL;
	current_token = tokens;
	state = EXPECTING_COMMAND;
	while (current_token)
	{
		consumed = handle_token(current_token, &state, &current_cmd, &commands, &last_cmd);
		if (consumed < 0)
		{
			free_commands(commands);
			return (NULL);
		}
		while (consumed > 0 && current_token)
		{
			current_token = current_token->next;
			consumed--;
		}
	}
	cmd_iter = commands;
	while (cmd_iter)
	{
		cmd_iter->args = remove_empty_args(cmd_iter->args);
		cmd_iter = cmd_iter->next;
	}
	return (commands);
}

t_command *parse_tokens(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	if (!validate_syntax(tokens))
	{
		printf("Syntax error in tokens\n");
		return (NULL);
	}
	return build_command_list(tokens);
}
