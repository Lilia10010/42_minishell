/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:51:10 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/02 14:51:18 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "token_types.h"
#include "context_types.h"

typedef struct s_token t_token;

t_token		*lexer_tokenize(char *input, t_context *ctx);
t_token		*create_token(t_token_type type, char *value);
void		add_token(t_token **head, t_token *new_token);
void		free_tokens(t_token *tokens);
char		*concatenate_strings(char *str1, char *str2);
void		debug_print_tokens(t_token *tokens);// RETIRAR SEGUELADA
void		skip_spaces(char **input);
int			is_shell_operator(char c);
char		*extract_quoted_token(char **input, char quote_char, t_context *ctx);
int			add_operator_token(t_token **tokens, char **current);

#endif