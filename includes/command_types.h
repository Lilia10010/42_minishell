/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:29:31 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 23:17:16 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TYPES_H
# define COMMAND_TYPES_H

typedef struct s_command
{
	char				**args;
	int					arg_count;
	int					arg_capacity;
	char				*input_file;
	char				**output_file;
	int					output_file_count;
	int					append_mode;
	int					heredoc_mode;
	char				*heredoc_delimiter;
	struct s_command	*next;
}	t_command;

#endif
