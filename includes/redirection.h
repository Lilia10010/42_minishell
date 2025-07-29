/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:53:00 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/28 23:49:01 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

typedef struct s_context	t_context;
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef enum e_builtin		t_builtin;

int	set_redirection(t_command *cmd, t_token *token, char *target);
int	execute_single_command(t_command *cmd, t_context *ctx);
#endif