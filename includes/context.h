#ifndef CONTEXT_H
#define CONTEXT_H

#include "lexer.h"
#include "parser.h"

typedef struct s_context
{
	t_token		*tokens;        // listagem de tokens gerados pelo lexer
	t_command	*commands;    // linting de comandos gerados pelo parser
	char		**envp;        // var de ambiente
	//int exit_code;          // code de saída do shell
} t_context;

#endif