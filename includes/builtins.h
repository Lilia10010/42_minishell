#ifndef BUILTINS_H
#define BUILTINS_H

# include "minishell.h"
typedef struct s_context t_context;

int builtin_echo(char **args, t_context *ctx);

#endif