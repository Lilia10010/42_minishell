/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_with_redirection.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:28:49 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/31 00:03:09 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "context_types.h"

int	execute_builtin_with_redirection(t_command *cmd, t_context *ctx)
{
	int	original_stdin;
	int	original_stdout;
	int	result;

	save_original_fds(&original_stdin, &original_stdout);
	if (!aplly_redirection(cmd))
	{
		restore_original_fds(original_stdin, original_stdout);
		ctx->exit_status = 1;
		return (1);
	}
	result = builtin_dispatcher(cmd, ctx);
	restore_original_fds(original_stdin, original_stdout);
	return (result);
}