/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:29:31 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/31 00:30:47 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_TYPES_H
# define COMMAND_TYPES_H

typedef struct s_command
{
	char				**args;
	int					arg_count;
	int					arg_capacity;
	char				*input_file; // <, <<
	char				*output_file; // >, >>
	int					append_mode;
	int					heredoc_mode;
	char				*heredoc_delimiter;
	struct s_command	*next; //vamos usar principalmente para implementar o pipes
}	t_command;

#endif