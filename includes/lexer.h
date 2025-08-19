/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:51:10 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/17 23:18:09 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token_types.h"

typedef struct s_token		t_token;
typedef struct s_context	t_context;

t_token		*lexer_tokenize(char *input, t_context *ctx);
t_token		*create_token(t_token_type type, char *value);
int			add_token(t_token **head, t_token *new_token);
void		free_tokens(t_token *tokens);
void		free_token(t_token *token);
char		*concatenate_strings(char *str1, char *str2);
void		skip_spaces(char **input);
int			is_shell_operator(char c);
char		*extract_quoted_token(char **input, char quote_char,
				t_context *ctx);
int			add_operator_token(t_token **tokens, char **current);
int			has_expandable_dollar(const char *str);
int			try_add_token(t_token **tokens, t_token_type type, char *value);
int			handle_redirect_out_operator(t_token **tokens, char **current);
int			create_and_add_token(t_token **tokens,
				t_token_type type, char *value);

#endif
