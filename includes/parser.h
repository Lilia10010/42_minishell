#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct s_command
{
	char *cmd;
}t_command;

t_command *parse_tokens(t_token *token);

#endif