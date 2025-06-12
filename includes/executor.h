#ifndef EXECUTOR_H
#define EXECUTOR_H

//#include "parser.h"
# include "minishell.h"

typedef struct s_context t_context;
typedef struct s_command t_command;

// Funções principais do executor
int     execute_command(t_command *commands, t_context *ctx);
int     is_builtin(char *cmd);
int     execute_builtin(t_command *cmd, t_context *ctx);

#endif