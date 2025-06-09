#ifndef LEXER_H
#define LEXER_H

typedef struct s_token
{
	char *command;
	struct s_token *next;
} t_token;

t_token	*lexer_tokenize(char *input);

#endif