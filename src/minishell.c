/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:37:37 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/06 18:02:02 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "context_types.h"
#include "prompt_defs.h"
#include "signals.h"

# include "lib_ft.h"

volatile sig_atomic_t g_signal_received = 0;

void init_context(t_context *ctx, char **envp)
{
	ctx->envp = envp;
	ctx->exit_status = 0;
	ctx->should_exit = 0;
	ctx->tokens = NULL;
	ctx->commands = NULL;
}

void cleanup_context(t_context *ctx)
{
	if (ctx->tokens)
	{
		free_tokens(ctx->tokens);
		ctx->tokens = NULL;
	}
	if (ctx->commands)
	{
		free_commands(ctx->commands);
		ctx->commands = NULL;
	}
}
static void handle_signal_in_loop(t_context *ctx)
{
    if (g_signal_received == SIGINT)
    {
        ctx->exit_status = 130;
        g_signal_received = 0;
		
    }
}

static void shell_loop(t_context *ctx)
{
	char *input;
	while (!ctx->should_exit)
	{
		//cleanup_context(ctx);
		handle_signal_in_loop(ctx);

		input = readline(MINI_PROMPT);
		if (!input)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			ctx->should_exit = 1;
			break;
		}
		if (g_signal_received)
		{
			ctx->exit_status = g_signal_received + 128;
			g_signal_received = 0;
		}
		 if (*input)
            add_history(input);
		ctx->tokens = lexer_tokenize(input, ctx);
		if (ctx->tokens)
		{
			ctx->commands = parse_tokens(ctx->tokens);
				//debug_print_commands(ctx->commands);
			if (ctx->commands)
			{
				execute_command(ctx->commands, ctx);
			}
		}
		free(input);	
	}
}

int main(int argc, char **argv, char **envp)
{
	t_context ctx;
	(void)argc;
	(void)argv;
	// printf("\n███████████████████████\n");
	// printf("█       MINIHELL      █\n");
	// printf("███████████████████████\n\n");

	init_context(&ctx, envp);
	setup_signals();
	shell_loop(&ctx);
	cleanup_context(&ctx);

	return (ctx.exit_status);
}

// readline – leitura do input do usuário
// lexer – quebra o input em tokens (respeitando aspas, escapes...) Lília
// parser – converte tokens em comandos (t_command) Lília
// comando externo – executa com fork + execve 
// echo lilia""11111111 remover aspas
// expansão de variáveis – substitui $VAR, $?, etc.
// redirecionamento (<, >, >>, <<)
// pipes –(|) conexão entre processos com pipe(), fork(), dup2()


// em execução: 
//
// sinais quase lá
// histórico de comandos – add_history(input) Mel
// builtins – echo, cd, pwd, exit, export, unset, env Mel


// heredoc – processa redirecionamentos << antes da execução
// norma
