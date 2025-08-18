/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ultils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 00:14:17 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/18 00:14:18 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include "utils.h"
#include "context_types.h"
#include "lexer.h"
#include "parser.h"

void	init_context(t_context *ctx, char **envp)
{
	ctx->envp = envp;
	ctx->exit_status = 0;
	ctx->should_exit = 0;
	ctx->tokens = NULL;
	ctx->commands = NULL;
}

void	cleanup_context(t_context *ctx)
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