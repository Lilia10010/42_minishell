
#include "minishell.h"
#include <stddef.h>
#include <stdio.h>
int tt_read_var(char **env)
{

    printf("hello -> main -> minishell.c");
    int i = 0;
    while(env[i] != NULL)
    {
        printf("env[%d]: %s\n",i, env[i]);
        ++i;
    }
    return (0);
}