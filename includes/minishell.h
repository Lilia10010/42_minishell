/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:52:50 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/04 18:36:48 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_context	t_context;

//void	shell_loop(t_context *ctx);
void	cleanup_context(t_context *ctx);
void	init_context(t_context *ctx, char **envp);

#endif