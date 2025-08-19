/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:47:39 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/19 12:30:17 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "executor.h"
#include "builtin.h"
#include "lib_ft.h"
#include "utils.h"

t_builtin	get_builtin_id(char *cmd)
{
	if (!cmd)
		return (BUILTIN_NONE);
	if (ft_strcmp(cmd, BUILTIN_NAME_ECHO) == 0)
		return (BUILTIN_ECHO);
	if (ft_strcmp(cmd, BUILTIN_NAME_CD) == 0)
		return (BUILTIN_CD);
	if (ft_strcmp(cmd, BUILTIN_NAME_PWD) == 0)
		return (BUILTIN_PWD);
	if (ft_strcmp(cmd, BUILTIN_NAME_EXPORT) == 0)
		return (BUILTIN_EXPORT);
	if (ft_strcmp(cmd, BUILTIN_NAME_UNSET) == 0)
		return (BUILTIN_UNSET);
	if (ft_strcmp(cmd, BUILTIN_NAME_ENV) == 0)
		return (BUILTIN_ENV);
	if (ft_strcmp(cmd, BUILTIN_NAME_EXIT) == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);
}

void	internal_exit_executor(t_context *ctx, int code)
{
	cleanup_context(ctx);
	cleanup_context_envp(ctx);
	clear_history();
	rl_clear_history();
	rl_free_line_state();
	exit(code);
}
