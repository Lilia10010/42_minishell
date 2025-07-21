/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:02:31 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/20 20:20:01 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "redirection.h"
#include "lib_ft.h"
#include "parser.h"
// Função auxiliar: inicializa novo comando e conecta à lista
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

// CORREÇÃO: Retorna quantos tokens foram consumidos
static int handle_redirection(t_token *token, t_command *cmd)
{
	t_token *target;

	target = token->next;
	if (!cmd)
	{
		printf("Syntax error: redirection without command\n");
		return (-1); // Erro
	}
	if (!target || target->type != TOKEN_WORD)
	{
		printf("Syntax error: redirection without target\n");
		return (-1); // Erro
	}
	if (!set_redirection(cmd, token, target->value))
	{
		return (-1); // Erro
	}
	return (2); // Consumiu 2 tokens (redirecionamento + target)
}

static int handle_word_token(t_token *token, t_parser_state *state, t_command **cmd, t_command **cmds, t_command **last)
{
	if (*state == EXPECTING_COMMAND)
	{
		if (!start_new_command(cmds, cmd, last))
			return (-1); // Erro
		if (!add_argument(*cmd, token->value))
			return (-1); // Erro ao adicionar argumento
		*state = EXPECTING_ARGS;
	}
	else if (*state == EXPECTING_ARGS)
	{
		if (!add_argument(*cmd, token->value))
			return (-1); // Erro ao adicionar argumento
	}
	else if (*state == EXPECTING_HEREDOC_DELIMITER)
	{
		(*cmd)->heredoc_delimiter = ft_strdup(token->value);
		if (!(*cmd)->heredoc_delimiter)
			return (-1); // Erro de memória
		(*cmd)->heredoc_mode = 1;
		*state = EXPECTING_ARGS;
	}
	return (1); // Consumiu 1 token
}

// Função auxiliar: processa pipe
static int handle_pipe_token(t_command *cmd, t_parser_state *state)
{
	if (!cmd)
	{
		printf("Syntax error: pipe without command\n");
		return (-1); // Erro
	}
	*state = EXPECTING_COMMAND;
	return (1); // Consumiu 1 token
}

// CORREÇÃO: Retorna quantos tokens foram consumidos
static int handle_token(t_token *token, t_parser_state *state, t_command **current_cmd, t_command **commands, t_command **last_cmd)
{
	int consumed;

	if (token->type == TOKEN_WORD)
	{
		consumed = handle_word_token(token, state, current_cmd, commands, last_cmd);
	}
	else if (is_redirection_token(token->type))
	{
		consumed = handle_redirection(token, *current_cmd);
	}
	else if (token->type == TOKEN_PIPE)
	{
		consumed = handle_pipe_token(*current_cmd, state);
	}
	else if (token->type == TOKEN_HEREDOC)
	{
		*state = EXPECTING_HEREDOC_DELIMITER;
		consumed = 1;
	}
	else
	{
		printf("Unknown token type: %d\n", token->type);
		consumed = -1; // Erro
	}

	return (consumed);
}

static t_command *build_command_list(t_token *tokens)
{
	t_command *commands, *current_cmd, *last_cmd;
	t_token *current_token;
	t_parser_state state;
	int consumed;

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

		// Avança o número correto de tokens
		while (consumed > 0 && current_token)
		{
			current_token = current_token->next;
			consumed--;
		}
	}
	// Validação final: não pode terminar esperando comando após pipe
	if (state == EXPECTING_COMMAND && commands)
	{
		printf("Syntax error: unexpected end of input after pipe\n");
		free_commands(commands);
		return (NULL);
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
