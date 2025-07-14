/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 23:53:00 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/13 23:53:21 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;

int	set_redirection(t_command *cmd, t_token *token, char *target);

#endif