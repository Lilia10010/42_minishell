/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:51:10 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/07/13 23:05:39 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN, // <
	TOKEN_REDIRECT_OUT, // >
	TOKEN_REDIRECT_OUT_APPEND, // >>
	TOKEN_HEREDOC, // <<
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_context	t_context;

t_token		*lexer_tokenize(char *input);
t_token		*create_token(t_token_type type, char *value);
void		add_token(t_token **head, t_token *new_token);
void		free_tokens(t_token *tokens);
char		*concatenate_strings(char *str1, char *str2);
void		debug_print_tokens(t_token *tokens);// RETIRAR SEGUELADA
void		skip_spaces(char **input);
int			is_shell_operator(char c);
char		*extract_quoted_token(char **input, char quote_char);
int			add_operator_token(t_token **tokens, char **current);

#endif