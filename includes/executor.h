/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:50:11 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/14 14:47:07 by microbiana       ###   ########.fr       */
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
t_builtin	get_builtin_id(char *cmd);
char		*find_executable_in_path(char *cmd, t_context *ctx);
int			is_path_comman(const char *cmd);
int			execute_path_command_absolut(t_command *cmd, t_context *ctx);
int			execute_command_from_path(t_command *cmd, t_context *ctx);
int			validate_redirection_file(char *filename, int is_output);
int			aplly_redirection(t_command *cmd, t_context *ctx);

int			execute_external_command_with_redirectons(t_command *cmd,
				t_context *ctx);
int			execute_builtin_with_redirection(t_command *cmd, t_context *ctx);
void		restore_original_fds(int fd_stdin, int fd_stdout);
void		save_original_fds(int *fd_stdin, int *fd_stdout);

void		ft_free_split(char **split);
#endif
