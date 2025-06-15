#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# include "lib_ft.h"

t_token *create_token(t_token_type type, char *value)
{
    t_token *token;

	token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    
    token->type = type;
   // token->value = value ? strdup(value) : NULL;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;

    token->next = NULL;
    return (token);
}

void add_token(t_token **head, t_token *new_token)
{
    if (!*head)
    {
        *head = new_token;
        return;
    }
    
    t_token *current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

t_token	*lexer_tokenize(char *input)
{
	t_token *tokens;
	char *current;
	char *word_start;
	char *word;
	int len;

	tokens = NULL;
	current = input;
	
	while (*current)
	{
		while (*current == ' ' || *current == '\t')
			current++;
		if (*current == '\0')
			break ;
		//TODO
		//[] criar handle pipes
		// [] handle redirections QUOTE [> >> , < <<]
		// [] handle words
		//ex: (mas no lugar dos ifs criar as handles)
		if (*current == '|')
		{
			//chama a função add_token e add o pipe
			printf("pipe detectado");
			current++;
		}
		else
		{
			word_start = current;
			
			len = 0;
			//encontrar o limit da string
			while (*current && *current != ' ' && *current != '\t' && *current != '|' && *current != '>' && *current != '<')
			{
				current++;
				len++;
			}
			word = malloc(len + 1);
			strncpy(word, word_start, len);
			word[len] = '\0';
			//printf("DEBUGZIM in lexer.c word [%s] size: [%d]\n", word, len);
			add_token(&tokens, create_token(TOKEN_WORD, word));
			free(word);
		}
	}
	 // debugzim dos token
    printf("DEBUG: Tokens criados:\n");
    t_token *debug_token = tokens;
    int token_count = 0;
	
    while (debug_token)
    {
        printf(" DEBUGZIM Token %d: tipo= %d, valor= '%s'\n", token_count++, debug_token->type, debug_token->value);
        debug_token = debug_token->next;
    }
	return (tokens);
}

void free_tokens(t_token *tokens)
{
	t_token *current;
	t_token *next;

	current = tokens;

	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
