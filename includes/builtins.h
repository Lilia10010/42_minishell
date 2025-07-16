#ifndef BUILTINS_H
#define BUILTINS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "../lib/lib_ft.h"

int	builtin_echo(char **args);
int	builtin_pwd(void);
int	builtin_env(char **args, t_context *ctx);
int	builtin_exit(char **args, t_context *ctx);
int	builtin_cd(char **args, t_context *ctx);

#endif