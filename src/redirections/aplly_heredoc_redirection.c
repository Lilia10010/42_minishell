/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aplly_heredoc_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:34:38 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/13 15:01:37 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>

#include "minishell.h"
#include "signals.h"
#include "command_types.h"
#include "lib_ft.h"
#include "context_types.h"
#include "lexer.h"
#include "env.h"



/* static void heredoc_sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    exit(130); // Código padrão para Ctrl+C
} */
static int	has_dollar(const char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '$')
		{
			char next = str[i + 1];

			// Se for último caractere, ou seguido de espaço/tab, ou caractere inválido, pula
			if (next == '\0' || next == ' ' || next == '\t' ||
				!(ft_isalnum(next) || next == '_' ))
			{
				i++;
				continue;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int aplly_heredoc_redirection(t_command *cmd, t_context *ctx)
{
    int     pipefd[2];
    pid_t   pid;
    char    *line = NULL;
    char    *expanded_line = NULL;

    if (!cmd || !cmd->heredoc_delimiter)
    {
        fprintf(stderr, "HEREDOC ERROR: cmd ou delimiter é NULL\n");
        return 0;
    }

    if (pipe(pipefd) == -1)
    {
		cleanup_context(ctx);
        perror("pipe");
        return 0;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
		cleanup_context(ctx);
        return 0;
    }

    if (pid == 0) // Processo filho: coleta o heredoc
    {
       // signal(SIGINT, heredoc_sigint_handler);
	   signal(SIGINT, SIG_DFL);
        close(pipefd[0]); // Filho escreve no pipe

        while (1)
        {
            line = readline("> ");
            if (!line)
            {
                fprintf(stderr,
                    "warning: here-document delimited by end-of-file (wanted `%s`)\n",
                    cmd->heredoc_delimiter);
                close(pipefd[1]);
                exit(0);
            }

            if (ft_strcmp(line, cmd->heredoc_delimiter) == 0)
            {
                free(line);
                break;
            }

            if (has_dollar(line))
            {
                expanded_line = expand_variables(line, ctx);
                free(line);
                line = expanded_line;
            }

            dprintf(pipefd[1], "%s\n", line);
            free(line);
        }

        close(pipefd[1]);
        exit(0);
    }

    // Processo pai: redireciona STDIN e espera o filho
    close(pipefd[1]); // Pai lê do pipe
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(pipefd[0]);
        return 0;
    }
    close(pipefd[0]);

    int status;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        ctx->exit_status = 130;
        g_signal_received = -1;
        return 0;
    }

    return 1;
}
