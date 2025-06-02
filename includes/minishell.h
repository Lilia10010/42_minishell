#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>

# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char	**env;
	int		exit_status;
	int		should_exit;
} t_shell;

int tt_read_var(char **env);
int init_shell(t_shell *shell, char **envp);
void cleanup_shell(t_shell *shell);

//funções de ambiente
char **copy_env(char **envp);
void free_env(char **env);

#endif