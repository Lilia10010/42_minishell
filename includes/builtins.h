/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:08:44 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/10 23:34:45 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_context	t_context;

typedef enum e_builtin
{
	BUILTIN_NONE = -1,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin;

# define BUILTIN_NAME_ECHO "echo"
# define BUILTIN_NAME_CD "cd"
# define BUILTIN_NAME_PWD "pwd"
# define BUILTIN_NAME_EXPORT "export"
# define BUILTIN_NAME_UNSET "unset"
# define BUILTIN_NAME_ENV "env"
# define BUILTIN_NAME_EXIT "exit"

int	builtin_echo(char **args, t_context *ctx);
int	builtin_cd(char **args, t_context *ctx);

#endif