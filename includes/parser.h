/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:46:45 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/11 13:44:52 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "token_types.h"

typedef struct s_command t_command;

typedef enum e_parser_state
{
	EXPECTING_COMMAND,
	EXPECTING_ARGS,
	EXPECTING_REDIRECT_TARGET,
	EXPECTING_HEREDOC_DELIMITER
} t_parser_state;

t_command	*parse_tokens(t_token *tokens);
int			is_redirection_token(t_token_type type);
int			validate_syntax(t_token *tokens);
void		free_commands(t_command *commands); 
t_command	*create_command(void);
int			add_argument(t_command *cmd, char *arg);
char		**remove_empty_args(char **args);
//debug
void		debug_print_commands(t_command *commands);


#endif