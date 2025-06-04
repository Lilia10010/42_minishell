#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>

int init_shell_test(t_shell *shell, char **envp)
{
    memset(shell, 0, sizeof(t_shell));
    
    shell->env = copy_env(envp);
    if (!shell->env)
        return (-1);
    
    shell->exit_status = 0;
    shell->should_exit = 0;
    
    return (0);
}

void cleanup_shell(t_shell *shell)
{
    if (shell->env)
        free_env(shell->env);
}

char **copy_env(char **envp)
{
    int     i;
    int     count;
    char    **new_env;
    
    count = 0;
    while (envp[count])
        count++;
    
    new_env = malloc(sizeof(char *) * (count + 1));
    if (!new_env)
        return (NULL);

    i = 0;
    while (i < count)
    {
        new_env[i] = strdup(envp[i]);
        if (!new_env[i])
        {
            free_env(new_env);
            return (NULL);
        }
        i++;
    }
    new_env[i] = NULL;
    
    return (new_env);
}

void free_env(char **env)
{
    int i;
    
    if (!env)
        return;
    
    i = 0;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}