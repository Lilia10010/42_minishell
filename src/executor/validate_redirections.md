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