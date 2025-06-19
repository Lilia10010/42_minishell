/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:52:50 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/18 22:54:20 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"
# include "env.h"
# include "signals.h"
# include "redirections.h"
# include "utils.h"

# include "../lib/lib_ft.h"

//contexto temporário do loop - tokens, cmd ...
typedef struct s_context
{
	char		**envp;
	int			exit_status;
	int			should_exit;
	t_token		*tokens;
	t_command	*commands;
}	t_context;

void	shell_loop(t_context *ctx);
void	cleanup_context(t_context *ctx);
void	init_context(t_context *ctx, char **envp);

#endif