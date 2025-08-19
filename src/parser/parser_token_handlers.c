
#include <stdio.h>
#include "parser.h"
#include "redirection.h"

static int	handle_pipe_token(t_command *cmd, t_parser_state *state)
{
	if (!cmd)
	{
		printf("Syntax error: pipe without command\n");
		return (-1);
	}
	*state = EXPECTING_COMMAND;
	return (1);
}

static int	handle_redirection(t_token *token, t_command *cmd)
{
	t_token	*target;

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
	return (2);
}

static int	handle_word_token(t_token *token, t_parser_context *ctx)
{
	if (*ctx->state == EXPECTING_COMMAND)
		return (handle_expecting_command(token, ctx));
	else if (*ctx->state == EXPECTING_ARGS)
	{
		if (!add_argument(*ctx->current_cmd, token->value))
			return (-1);
	}
	else if (*ctx->state == EXPECTING_HEREDOC_DELIMITER)
		return (handle_expecting_heredoc(token, ctx));
	return (1);
}

int	handle_token(t_token *token, t_parser_context *ctx)
{
	int	consumed;

	if (token->type == TOKEN_WORD)
		consumed = handle_word_token(token, ctx);
	else if (is_redirection_token(token->type))
		consumed = handle_redirection(token, *ctx->current_cmd);
	else if (token->type == TOKEN_PIPE)
		consumed = handle_pipe_token(*ctx->current_cmd, ctx->state);
	else if (token->type == TOKEN_HEREDOC)
	{
		*ctx->state = EXPECTING_HEREDOC_DELIMITER;
		consumed = 1;
	}
	else
	{
		printf("Unknown token type: %d\n", token->type);
		consumed = -1;
	}
	return (consumed);
}
