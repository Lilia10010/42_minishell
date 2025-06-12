#ifndef LEXER_H
#define LEXER_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
} t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
} t_token;

t_token	*lexer_tokenize(char *input);
void free_tokens(t_token *tokens);
t_token *create_token(t_token_type type, char *value);
void add_token(t_token **head, t_token *new_token);



#endif