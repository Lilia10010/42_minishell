/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:25:45 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/07 22:58:58 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


static int start_new_command(t_command **commands, t_command **current, t_command **last)
{
	*current = create_command();
	if (!*current)
		return (0);
	if (!*commands)
		*commands = *current;
	else
		(*last)->next = *current;
	*last = *current;
	return (1);
}

static int handle_redirection(t_token **token, t_command *cmd, t_command *commands)
{
	t_token *redir;
	t_token *target;

	redir = *token;
	target = redir->next;
	if (!cmd)
	{
		printf("syntax error: redirection without command\n");
		free_commands(commands);
		return (0);
	}
	if (!target || target->type != TOKEN_WORD)
	{
		printf("syntax error: redirection without target");
		free_commands(commands);
	}
	if (!set_redirection(cmd, redir, target->value))
	{
		free_commands(commands);
		return (0);
	}
	*token = target;
	return (1);
}