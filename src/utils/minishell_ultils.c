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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "context_types.h"
#include "lexer.h"
#include "parser.h"
#include "lib_ft.h"

static size_t	count_envp_entries(char **envp)
{
	size_t	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

static int	copy_envp_entries(t_context *ctx, char **envp, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		ctx->envp[i] = ft_strdup(envp[i]);
		if (!ctx->envp[i])
		{
			printf("Error: Failed to duplicate envp[%zu]: %s\n", i, envp[i]);
			while (i-- > 0)
				free(envp[i]);
			free(envp);
			ctx->envp = NULL;
			return (0);
		}
		i++;
	}
	ctx->envp[count] = NULL;
	return (1);
}

void	init_context(t_context *ctx, char **envp)
{
	size_t	count;

	if (!ctx)
		return ;
	ctx->exit_status = 0;
	ctx->should_exit = 0;
	ctx->tokens = NULL;
	ctx->commands = NULL;
	count = count_envp_entries(envp);
	ctx->envp = malloc(sizeof(char *) * (count + 1));
	if (!ctx->envp)
	{
		printf("Error: Failed to allocate memory for ctx->envp\n");
		ctx->envp = NULL;
		return ;
	}
	copy_envp_entries(ctx, envp, count);
}

void	cleanup_context(t_context *ctx)
{
	if (!ctx)
		return ;
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

void	cleanup_context_envp(t_context *ctx)
{
	size_t	i;

	i = 0;
	if (!ctx)
		return ;
	if (ctx->envp)
	{
		while (ctx->envp[i])
		{
			free(ctx->envp[i]);
			i++;
		}
		free(ctx->envp);
		ctx->envp = NULL;
	}
}
