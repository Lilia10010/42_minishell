/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command_2_test.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:16:52 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/28 16:20:21 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <sys/types.h> // Required for pid_t
#include "minishell.h"
#include "parser.h"
#include "builtin.h"
#include "executor.h"
#include "lib_ft.h"


// static int apply_redirections(t_command *cmd)
// {
//     printf("Applying command: %s\n", cmd->args[0]);
// 	return (1); 
// }
//função inicial
// int execute_single_command(t_command *cmd, t_context *ctx)
// {	
// 	if (!cmd || !cmd->args || !cmd->args[0])
// 	{
// 		ctx->exit_status = 0;
// 		return (0);
// 		//return (ctx->exit_status = 0, 0); pode?
// 	}
// 	if (get_builtin_id(cmd->args[0]) != BUILTIN_NONE)
// 		return (builtin_dispatcher(cmd, ctx));
// 	if (is_path_comman(cmd->args[0]))
// 		return (execute_path_command(cmd, ctx));
// 	return (execute_command_from_path(cmd, ctx));

// }


//testes com redirecionamentos
/* Função para aplicar redirecionamento de entrada */
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

/* Função para aplicar redirecionamento de saída */
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

/* Função para lidar com heredoc */
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
    // while ((line = get_next_line(STDIN_FILENO)) != NULL)
    // {
    //     // Remove o \n do final se existir
    //     if (line[ft_strlen(line) - 1] == '\n')
    //         line[ft_strlen(line) - 1] = '\0';

    //     if (ft_strcmp(line, cmd->heredoc_delimiter) == 0)
    //     {
    //         free(line);
    //         break;
    //     }

    //     write(pipefd[1], line, ft_strlen(line));
    //     write(pipefd[1], "\n", 1);
    //     free(line);
    //     printf("heredoc> ");
    // }

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

/* Função principal para aplicar todos os redirecionamentos */
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

/* Função para salvar os file descriptors originais */
void save_original_fds(int *original_stdin, int *original_stdout)
{
    *original_stdin = dup(STDIN_FILENO);
    *original_stdout = dup(STDOUT_FILENO);
}

/* Função para restaurar os file descriptors originais */
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

// /* Versão atualizada do execute_single_command com redirecionamentos */
// int execute_single_command(t_command *cmd, t_context *ctx)
// {
//     int original_stdin, original_stdout;
//     int result;

//     if (!cmd || !cmd->args || !cmd->args[0])
//     {
//         ctx->exit_status = 0;
//         return (0);
//     }

//     // Salva os file descriptors originais
//     save_original_fds(&original_stdin, &original_stdout);

//     // Aplica redirecionamentos
//     if (!apply_redirections(cmd))
//     {
//         restore_original_fds(original_stdin, original_stdout);
//         ctx->exit_status = 1;
//         return (1);
//     }

//     // Executa o comando
//     if (get_builtin_id(cmd->args[0]) != BUILTIN_NONE)
//         result = builtin_dispatcher(cmd, ctx);
//     else if (is_path_command(cmd->args[0]))
//         result = execute_path_command(cmd, ctx);
//     else
//         result = execute_command_from_path(cmd, ctx);

//     // Restaura os file descriptors originais
//     restore_original_fds(original_stdin, original_stdout);

//     return (result);
// }

/* Exemplo de implementação para comando simples com redirecionamento */
int execute_single_command(t_command *cmd, t_context *ctx)
{
    pid_t pid;
    int status;
    int original_stdin, original_stdout;

    // Salva FDs originais
    save_original_fds(&original_stdin, &original_stdout);

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        restore_original_fds(original_stdin, original_stdout);
        return (1);
    }

    if (pid == 0) // Processo filho
    {
        // Aplica redirecionamentos no processo filho
        if (!apply_redirections(cmd))
            exit(1);

        // Executa o comando
        if (execvp(cmd->args[0], cmd->args) == -1)
        {
            perror(cmd->args[0]);
            exit(127);
        }
    }
    else // Processo pai
    {
        waitpid(pid, &status, 0);
        restore_original_fds(original_stdin, original_stdout);
        
        if (WIFEXITED(status))
            ctx->exit_status = WEXITSTATUS(status);
        else
            ctx->exit_status = 1;
    }

    return (ctx->exit_status);
}

/* Função auxiliar para verificar se é um token de redirecionamento */
// static int is_redirection_token(t_token_type token_type)
// {
//     return (token_type == TOKEN_REDIRECT_IN ||
//             token_type == TOKEN_REDIRECT_OUT ||
//             token_type == TOKEN_REDIRECT_OUT_APPEND ||
//             token_type == TOKEN_HEREDOC);
// }

/* Função para validar se o arquivo pode ser criado/aberto */
int validate_redirection_file(char *filename, int is_output)
{
    int fd;

    if (!filename)
        return (0);

    if (is_output)
    {
        // Tenta criar/abrir o arquivo para escrita
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
        // Verifica se o arquivo existe e pode ser lido
        fd = open(filename, O_RDONLY);
        if (fd == -1)
        {
            perror(filename);
            return (0);
        }
        close(fd);
    }

    return (1);
}