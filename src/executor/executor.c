/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:20:59 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/14 13:08:50 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "executor.h"
#include "command_types.h"

int	execute_command(t_command *commands, t_context *ctx)
{
	if (!commands)
		return (0);
	if (!commands->next)
		return (execute_single_command(commands, ctx));
	return (execute_pipe(commands, ctx));
}
