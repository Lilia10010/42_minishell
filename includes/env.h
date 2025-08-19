/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:49:50 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/18 21:48:55 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_context	t_context;

char	*expand_variables(const char *input, t_context *ctx);
int		check_envp_params(char **envp, char *name);
void	free_cpy_envp(char **envp);
int		get_envp_index(char *key, char **envp);
char	**create_new_env_var(char **old_envp, char *var, int size, int i);
char	*get_env_value(const char *key, t_context *ctx);
char	*get_env_value2(const char *key, t_context *ctx);
int		find_var(char **envp, char *name);
char	*create_envp_string(char *name, char *value);
int		set_env(char ***envp, char *name_var, char *value);
int		set_env_var(t_context *ctx, char *var);
int		count_envp_vars(char **envp);
void	sorted_envp(char **envp);
int		unset_envp_var(t_context *ctx, char *key);

#endif
