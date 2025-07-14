/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:52:50 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/13 22:57:04 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;

#define GREEN "\001\033[1;32m\002"
#define RESET_COLOR "\001\033[0m\002"
#define GREEN_BG     "\001\033[42m\002"
#define ROSA "\001\033[48;5;206m\002"
#define BOLD "\001\033[1m\002"


//#define MATRIX_PROMPT "\033[1;32m\033[40m minishell$ " RESET_COLOR
//#define MATRIX_PROMPT "\033[1;32m\033[40m minishell$ " RESET_COLOR
//#define MATRIX_PROMPT "\033[30m" GREEN_BG " minishell$ " RESET_COLOR
#define MATRIX_PROMPT ROSA BOLD " minishell$ " RESET_COLOR " "

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