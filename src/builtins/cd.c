#include "builtins.h"
#include <stdio.h>
#include <string.h>


int	builtin_cd(char **args, t_context *ctx)
{
	(void)args;
	(void)ctx;
   printf("executando builtin cdzim\n");
   while (*args)
   {
	printf("executando builtin cdzim %s \n", *args++);
   }
    return (0);
}