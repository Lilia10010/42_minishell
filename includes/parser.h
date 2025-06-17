#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct s_command
{
	char				**args;
	char				*input_file;
	char				*output_file;
	int					append_output;
	char				*heredoc_delimiter;
	struct s_command	*next; //vamos usar principalmente para implementar o pipes
} t_command;

t_command *parse_tokens(t_token *tokens);
t_command *create_command(void);
void free_commands(t_command *commands);
int count_word_tokens(t_token *tokens);

#endif