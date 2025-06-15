/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:37:37 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/14 23:33:51 by lpaula-n         ###   ########.fr       */
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
		input = readline("minishell$ ");
		if (!input) //algum comando de scape
		{
			printf("exit\n"); // não pode ter o \n aqui
			break ;
		}

		//começa o processamento do input
		ctx->tokens = lexer_tokenize(input);
		if (ctx->tokens)
		{
			ctx->commands = parse_tokens(ctx->tokens);
			if (ctx->commands)
				execute_command(ctx->commands, ctx);
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

//1 - readline
//2 - lexer + parse
// tudo ok
//3 - executor