/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:56:11 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 22:54:22 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_context	t_context;

void	ft_free_split(char **split);
void	init_context(t_context *ctx, char **envp);
void	cleanup_context(t_context *ctx);

#endif