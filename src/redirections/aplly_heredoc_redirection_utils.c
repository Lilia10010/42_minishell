/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aplly_heredoc_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:34:38 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/15 21:15:29 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "command_types.h"
#include "lib_ft.h"
#include "context_types.h"
#include "utils.h"
#include "lexer.h"
#include "env.h"
#include "minishell.h"

char	*process_line_expansion(char *line, t_context *ctx)
{
	char	*expanded;

	if (has_expandable_dollar(line))
	{
		expanded = expand_variables(line, ctx);
		free(line);
		return (expanded);
	}
	return (line);
}

void	internal_exit_heredoc(t_context *ctx, int code)
{
	cleanup_context(ctx);
	cleanup_context_envp(ctx);
	clear_history();
	rl_clear_history();
	rl_free_line_state();
	exit(code);
}

int	validate_heredoc_params(t_command *cmd)
{
	if (!cmd || !cmd->heredoc_delimiter)
	{
		ft_putstr_fd("HEREDOC ERROR: cmd ou delimiter é NULL\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (0);
	}
	return (1);
}

void	handle_message_end_of_file(char *delimiter)
{
	ft_putstr_fd("bash: warning: here-document delimited", STDERR_FILENO);
	ft_putstr_fd(" by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}
