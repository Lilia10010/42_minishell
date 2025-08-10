/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aplly_heredoc_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 21:34:38 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/10 18:58:49 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "command_types.h"

int aplly_heredoc_redirection(t_command *cmd)
{
	(void)cmd;
	printf("HEREDOC\n");
	int i = 0;
	while (cmd->args[i])
	{
		printf("ARG[%d]: %s\n", i, cmd->args[i]);
		i++;
	}
	return (1);
}