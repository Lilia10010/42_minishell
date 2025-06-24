/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:51:10 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/23 22:22:37 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_STRING,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_OUT_APPEND, // >>
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_END 
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token		*lexer_tokenize(char *input);
void		free_tokens(t_token *tokens);
t_token		*create_token(t_token_type type, char *value);
void		add_token(t_token **head, t_token *new_token);


#endif