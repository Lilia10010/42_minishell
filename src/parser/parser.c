#include "parser.h"
#include <string.h>
#include <stdlib.h>

t_command *parse_tokens(t_token *token)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd = strdup(token->command);
	return (cmd);
}
