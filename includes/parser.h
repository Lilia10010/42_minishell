/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:46:45 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 19:12:12 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token_types.h"

typedef struct s_command	t_command;
typedef struct s_context	t_context;

typedef enum e_parser_state
{
	EXPECTING_COMMAND,
	EXPECTING_ARGS,
	EXPECTING_REDIRECT_TARGET,
	EXPECTING_HEREDOC_DELIMITER
}	t_parser_state;

typedef struct s_parser_context
{
	t_parser_state	*state;
	t_command		**current_cmd;
	t_command		**commands;
	t_command		**last_cmd;
}	t_parser_context;

t_command	*parse_tokens(t_token *tokens, t_context *ctx);
int			is_redirection_token(t_token_type type);
int			validate_syntax(t_token *tokens);
void		free_commands(t_command *commands);
t_command	*create_command(void);
int			add_argument(t_command *cmd, char *arg);
char		**remove_empty_args(char **args);
int			handle_token(t_token *token, t_parser_context *ctx);
void		cleanup_commands(t_command *commands);
int			handle_expecting_command(t_token *token, t_parser_context *ctx);
int			handle_expecting_heredoc(t_token *token, t_parser_context *ctx);
//debug
void		debug_print_commands(t_command *commands);

#endif
