/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 23:53:43 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/13 18:13:16 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_TYPES_H
# define CONTEXT_TYPES_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;

typedef struct s_context
{
	char		**envp;
	int			exit_status;
	int			should_exit;
	t_token		*tokens;
	t_command	*commands;
}	t_context;

#endif
