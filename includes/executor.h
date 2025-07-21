/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:50:11 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/20 22:07:23 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_context	t_context;
typedef struct s_command	t_command;
typedef enum e_builtin		t_builtin;

int			execute_command(t_command *commands, t_context *ctx);
t_builtin	get_builtin_id(char *cmd);
int			builtin_dispatcher(t_command *cmd, t_context *ctx);
int			execute_single_command(t_command *cmd, t_context *ctx);
int			execute_pipeline(t_command *cmd, t_context *ctx);
void		execute_external_command(t_command *cmd, t_context *ctx);
t_builtin	get_builtin_id(char *cmd);
char		*find_executable_in_path(const char *cmd);

//criar um arquivo .h para funções de free
void	ft_free_split(char **split);
#endif