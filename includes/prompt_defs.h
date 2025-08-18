/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_defs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:23:26 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/18 00:18:56 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_DEFS_H
# define PROMPT_DEFS_H

# define RESET_COLOR "\001\033[0m\002"
# define ROSA "\001\033[48;5;206m\002"
# define BOLD "\001\033[1m\002"

//# define MINI_PROMPT ROSA BOLD " minishell$ " RESET_COLOR " "
# define MINI_PROMPT "\001\033[48;5;206m\002\001\033[1m\002 minishell$ \001\033[0m\002 "
#endif
