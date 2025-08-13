/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:53:00 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/13 18:29:20 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

typedef struct s_context	t_context;
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef enum e_builtin		t_builtin;

int	set_redirection(t_command *cmd, t_token *token, char *target);
int	execute_single_command(t_command *cmd, t_context *ctx);
int	aplly_heredoc_redirection(t_command *cmd);

#endif
