/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:50:11 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/28 16:19:15 by microbiana       ###   ########.fr       */
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
int			execute_pipe(t_command *cmd, t_context *ctx);
//int			execute_external_command(t_command *cmd, t_context *ctx, char *path);
t_builtin	get_builtin_id(char *cmd);
char		*find_executable_in_path(const char *cmd);
int			is_path_comman(const char *cmd);
int			execute_path_command(t_command *cmd, t_context *ctx);
int			execute_command_from_path(t_command *cmd, t_context *ctx);
int			validate_redirection_file(char *filename, int is_output);

//criar um arquivo .h para funções de free
void	ft_free_split(char **split);
#endif