#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


t_token	*lexer_tokenize(char *input)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->command = strdup(input);
	return (token);
}
