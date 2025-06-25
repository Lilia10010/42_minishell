/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:37:37 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/24 23:45:57 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>


void init_context(t_context *ctx, char **envp)
{
	ctx->envp = envp;
	ctx->exit_status = 0;
	ctx->should_exit = 0;
	ctx->tokens = NULL;
	ctx->commands = NULL;
}

//serve para limpar dados da interação anterior
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

void shell_loop(t_context *ctx)
{
	char *input;

	while (!ctx->should_exit)
	{
		cleanup_context(ctx);
		input = readline(MATRIX_PROMPT);
		if (!input) //algum comando de scape
		{
			printf("exit\n"); // não pode ter o \n aqui
			ctx->should_exit = 1;
			break ;
		}

		//começa o processamento do input
		ctx->tokens = lexer_tokenize(input);
		if (ctx->tokens)
		{
			ctx->commands = parse_tokens(ctx->tokens);
			if (ctx->commands)
			{
				debug_print_commands(ctx->commands);
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

	init_context(&ctx, envp);
	shell_loop(&ctx);
	cleanup_context(&ctx);

	return (ctx.exit_status);
}

// readline – leitura do input do usuário
// histórico de comandos – add_history(input)
// expansão de variáveis – substitui $VAR, $?, etc.
// lexer – quebra o input em tokens (respeitando aspas, escapes...)
// parser – converte tokens em comandos (t_command)
// heredoc – processa redirecionamentos << antes da execução
// AST (pode ser linear, mas pode evoluir para árvore)
// executor – responsável por:
// pipes (|)
// redirecionamento (<, >, >>, <<)
// builtins
// comandos externos
// builtins – echo, cd, pwd, exit, export, unset, env
// comando externo – executa com fork + execve
// redirecionamento – gerencia dup2, abertura/fechamento de arquivos
// pipes – conexão entre processos com pipe(), fork(), dup2()




