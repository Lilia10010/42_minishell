/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:37:37 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/09 00:09:37 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>


void init_miniloop(t_context *ctx)
{
	ctx->tokens = NULL;
	ctx->commands = NULL;
}

static void shell_loop(t_context *ctx)
{
	char		*input;

	while (1)
	{
		init_miniloop(ctx); // reseta variáveis temporárias 
		input = readline("minishell$ ");
		if (!input)
			break;
		//history deve excluir o histórico vindo do heredoc
		if (*input)
			add_history(input);
		
		ctx->tokens = lexer_tokenize(input);
		ctx->commands = parse_tokens(ctx->tokens);

		if (ctx->commands)
			execute_command(ctx->commands);

		//dar free em tokens - command - input
	// 	free_tokens(tokens);
	// 	free_command(cmd);
	// 	free(input);
	// }
	}

}

int main(int argc, char **argv, char **envp)
{
	t_context ctx;
	(void)argc;
	(void)argv;

	ctx.envp = envp;
	ctx.tokens = NULL;
	ctx.commands = NULL;
	

	

	//init_minishell(envp);
	shell_loop(&ctx);

	//cleanup_minishell();
	//return (g_data.exit_code); //aqui vem o codido que foi finalizado ou o return normal
	return (0);
}

//1 - readline
//2 - lexer + parse
// tudo ok
//3 - executor