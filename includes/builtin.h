/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:08:44 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/13 18:10:45 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "builtin_types.h"

typedef struct s_context	t_context;

# define BUILTIN_NAME_ECHO "echo"
# define BUILTIN_NAME_CD "cd"
# define BUILTIN_NAME_PWD "pwd"
# define BUILTIN_NAME_EXPORT "export"
# define BUILTIN_NAME_UNSET "unset"
# define BUILTIN_NAME_ENV "env"
# define BUILTIN_NAME_EXIT "exit"

int	builtin_echo(char **args, t_context *ctx);
int	builtin_pwd(char **args, t_context *ctx);
int	builtin_env(char **args, t_context *ctx);
int	builtin_exit(char **args, t_context *ctx);
int	builtin_cd(char **args, t_context *ctx);
int	builtin_unset(char **args, t_context *ctx);
int	builtin_export(char **args, t_context *ctx);

#endif
