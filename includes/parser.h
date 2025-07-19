/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:46:45 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/18 22:23:35 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

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

typedef enum e_parser_state
{
	EXPECTING_COMMAND,
	EXPECTING_ARGS,
	EXPECTING_REDIRECT_TARGET,
	EXPECTING_HEREDOC_DELIMITER
} t_parser_state;

t_command	*parse_tokens(t_token *tokens);
int			is_redirection_token(t_token_type type);
int validate_syntax(t_token *tokens);
void free_command(t_command *cmd);
void free_commands(t_command *commands);
t_command *create_command(void);
int add_argument(t_command *cmd, char *arg);

//debug
void debug_print_commands(t_command *commands);
// t_command	*create_command(void);
// void		free_commands(t_command *commands);
// int			count_word_tokens(t_token *tokens);


#endif