#include "parser.h"
#include <string.h>
#include <stdlib.h>

//o parse vai converter os toknes em estruturas de comando
t_command *create_command(void)
{
	t_command *cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_output = 0;
	cmd->heredoc_delimiter = NULL;
	cmd->next = NULL;
	return (cmd);

}

int count_word_tokens(t_token *tokens)
{
	t_token *current;
	int count;

	current = tokens;
	count = 0;

	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD)
			count++;
		current = current->next;
	}
	return (count);
}

t_command *parse_tokens(t_token *tokens)
{
	
	if (!tokens)
	return (NULL);
	
	t_command *current_cmd;
	t_command *commands;
	t_token *token;
	t_token *word_token;
	int arg_count;
	int i;

	i = 0;
	token = tokens;
	current_cmd = NULL;
	commands = NULL;

	while (token)
	{
		if (!current_cmd)
		{
			current_cmd = create_command();
			if (!commands)
				commands = current_cmd;
		}
		if (token->type == TOKEN_WORD)
		{
			//ver quantos argumentos tem por comando
			arg_count = count_word_tokens(token);
			current_cmd->args = malloc(sizeof(char*) * (arg_count + 1));

			//pode ser um handle separado 
			i = 0;
			word_token = token;
			while (word_token && word_token->type != TOKEN_PIPE)
			{
				if (word_token->type == TOKEN_WORD)
				{
					current_cmd->args[i] = strdup(word_token->value);
					i++;
				}
				word_token = word_token->next;
			}
			current_cmd->args[i] = NULL;

			//para pular o token q já foi processado
			token = word_token;
		}
		else if (token->type == TOKEN_PIPE)
		{
			current_cmd->next = create_command();
			current_cmd = current_cmd->next;
			token = token->next;
		}
		else if (token->type == TOKEN_REDIRECT_OUT)
		{
			//TBM CRIAR HANDLE
		}
		else if (token->type == TOKEN_REDIRECT_IN)
		{
			//TBM CRIAR HANDLE
		}
		else
			token = token->next;
	}
	return (commands);
}

void free_commands(t_command *commands)
{
	t_command *current;
	t_command *next;
	int i;

	current = commands;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				free((current->args[i]));
				++i;
			}
			free(current->args);
		}
		free(current->input_file);
		free(current->output_file);
		free(current->heredoc_delimiter);
		free(current);
		current = next;
	}
}