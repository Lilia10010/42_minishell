/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:16:52 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/28 16:18:20 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <sys/types.h>
#include "minishell.h"
#include "parser.h"
#include "builtin.h"
#include "executor.h"
#include "lib_ft.h"
#include "builtin.h"


static int apply_input_redirection(t_command *cmd)
{
    int fd;

    if (!cmd->input_file)
        return (1);

    fd = open(cmd->input_file, O_RDONLY);
    if (fd == -1)
    {
        perror(cmd->input_file);
        return (0);
    }

    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2 input");
        close(fd);
        return (0);
    }

    close(fd);
    return (1);
}

static int apply_output_redirection(t_command *cmd)
{
    int fd;
    int flags;

    if (!cmd->output_file)
        return (1);

    if (cmd->append_mode)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
        flags = O_WRONLY | O_CREAT | O_TRUNC;

    fd = open(cmd->output_file, flags, 0644);
    if (fd == -1)
    {
        perror(cmd->output_file);
        return (0);
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2 output");
        close(fd);
        return (0);
    }

    close(fd);
    return (1);
}

static int apply_heredoc_redirection(t_command *cmd)
{
    int pipefd[2];
    //char *line;

    if (!cmd->heredoc_mode || !cmd->heredoc_delimiter)
        return (1);

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (0);
    }

    printf("heredoc> ");
    /* while ((line = get_next_line(STDIN_FILENO)) != NULL)
    {
        // Remove o \n do final se existir
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';

        if (ft_strcmp(line, cmd->heredoc_delimiter) == 0)
        {
            free(line);
            break;
        }

        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
        printf("heredoc> ");
    } */

    close(pipefd[1]);

    if (dup2(pipefd[0], STDIN_FILENO) == -1)
    {
        perror("dup2 heredoc");
        close(pipefd[0]);
        return (0);
    }

    close(pipefd[0]);
    return (1);
}

int apply_redirections(t_command *cmd)
{
    if (!cmd)
        return (1);

    // Aplica redirecionamento de entrada (< ou <<)
    if (cmd->heredoc_mode)
    {
        if (!apply_heredoc_redirection(cmd))
            return (0);
    }
    else if (cmd->input_file)
    {
        if (!apply_input_redirection(cmd))
            return (0);
    }

    // Aplica redirecionamento de saída (> ou >>)
    if (cmd->output_file)
    {
        if (!apply_output_redirection(cmd))
            return (0);
    }

    return (1);
}

void save_original_fds(int *original_stdin, int *original_stdout)
{
    *original_stdin = dup(STDIN_FILENO);
    *original_stdout = dup(STDOUT_FILENO);
}

void restore_original_fds(int original_stdin, int original_stdout)
{
    if (original_stdin != -1)
    {
        dup2(original_stdin, STDIN_FILENO);
        close(original_stdin);
    }
    if (original_stdout != -1)
    {
        dup2(original_stdout, STDOUT_FILENO);
        close(original_stdout);
    }
}

/* Executa comando builtin com redirecionamento */
static int execute_builtin_with_redirections(t_command *cmd, t_context *ctx)
{
    int original_stdin, original_stdout;
    int result;

    // Salva os file descriptors originais
    save_original_fds(&original_stdin, &original_stdout);

    // Aplica redirecionamentos
    if (!apply_redirections(cmd))
    {
        restore_original_fds(original_stdin, original_stdout);
        ctx->exit_status = 1;
        return (1);
    }

    // Executa o builtin diretamente no processo atual
    result = builtin_dispatcher(cmd, ctx);

    // Restaura os file descriptors originais
    restore_original_fds(original_stdin, original_stdout);

    return (result);
}

/* Executa comando externo com redirecionamento */
static int execute_external_with_redirections(t_command *cmd, t_context *ctx)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        ctx->exit_status = 1;
        return (1);
    }

    if (pid == 0) // Processo filho
    {
        // Aplica redirecionamentos no processo filho
        if (!apply_redirections(cmd))
            exit(1);

        // Executa o comando externo
       /*  if (is_path_command(cmd->args[0]))
        {
            if (execve(cmd->args[0], cmd->args, ctx->envp) == -1)
            {
                perror(cmd->args[0]);
                exit(127);
            }
        } */
        else
        {
            if (execvp(cmd->args[0], cmd->args) == -1)
            {
                perror(cmd->args[0]);
                exit(127);
            }
        }
    }
    else // Processo pai
    {
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status))
            ctx->exit_status = WEXITSTATUS(status);
        else
            ctx->exit_status = 1;
    }

    return (ctx->exit_status);
}

/* Função principal melhorada para executar comandos */
int execute_single_command(t_command *cmd, t_context *ctx)
{
    if (!cmd || !cmd->args || !cmd->args[0])
    {
        ctx->exit_status = 0;
        return (0);
    }

    // Verifica se é um comando builtin
    if (get_builtin_id(cmd->args[0]) != BUILTIN_NONE)
    {
        // Para builtins, executa diretamente sem fork
        return execute_builtin_with_redirections(cmd, ctx);
    }
    else
    {
        // Para comandos externos, usa fork
        return execute_external_with_redirections(cmd, ctx);
    }
}

/* Função para validar redirecionamentos antes da execução */
int validate_redirections(t_command *cmd)
{
    // Valida arquivo de entrada
    if (cmd->input_file)
    {
        if (!validate_redirection_file(cmd->input_file, 0))
            return (0);
    }

    // Valida arquivo de saída
    if (cmd->output_file)
    {
        if (!validate_redirection_file(cmd->output_file, 1))
            return (0);
    }

    // Validações adicionais para heredoc
    if (cmd->heredoc_mode && !cmd->heredoc_delimiter)
    {
        fprintf(stderr, "minishell: syntax error: heredoc without delimiter\n");
        return (0);
    }

    return (1);
}

int validate_redirection_file(char *filename, int is_output)
{
    int fd;

    if (!filename)
        return (0);

    if (is_output)
    {
        // Para saída, tenta criar/abrir o arquivo
        fd = open(filename, O_WRONLY | O_CREAT, 0644);
        if (fd == -1)
        {
            perror(filename);
            return (0);
        }
        close(fd);
    }
    else
    {
        // Para entrada, verifica se o arquivo existe
        if (access(filename, F_OK) == -1)
        {
            perror(filename);
            return (0);
        }
        // Verifica se pode ser lido
        if (access(filename, R_OK) == -1)
        {
            perror(filename);
            return (0);
        }
    }

    return (1);
}