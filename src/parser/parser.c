#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

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

	while (current && current->type != TOKEN_PIPE &&
		   current->type != TOKEN_REDIRECT_OUT &&
		   current->type != TOKEN_REDIRECT_OUT_APPEND &&
		   current->type != TOKEN_REDIRECT_IN &&
		   current->type != TOKEN_HEREDOC)
	{
		if (current->type == TOKEN_WORD)
			count++;
		current = current->next;
	}
	return (count);
}
t_command *parse_tokens(t_token *tokens)
{
	t_command *current_cmd;
	t_command *commands;
	t_token *token;

	if (!tokens)
		return (NULL);

	token = tokens;
	current_cmd = NULL;
	commands = NULL;

	// if (!validate_syntax(tokens))
	// 	return (NULL);

	while (token)
	{
		if (!current_cmd)
		{
			current_cmd = create_command();
			if (!current_cmd)
			{
				free_commands(commands);
				return (NULL);
			}
			if (!commands)
				commands = current_cmd;
		}
		if (token->type == TOKEN_WORD)
		{
			token = collect_args(token, &current_cmd->args);
			continue ;
		}
		else if (token->type == TOKEN_REDIRECT_OUT || token->type == TOKEN_REDIRECT_OUT_APPEND)
		{
			if (token->next && token->next->type == TOKEN_WORD)
			{
				current_cmd->output_file = ft_strdup(token->next->value);
				current_cmd->append_output = (token->type == TOKEN_REDIRECT_OUT_APPEND);
				token = token->next->next;
			}
			else
				return (free_commands(commands), NULL);
		}
		else if (token->type == TOKEN_REDIRECT_IN)
		{
			if (token->next && token->next->type == TOKEN_WORD)
			{
				current_cmd->input_file = ft_strdup(token->next->value);
				token = token->next->next;
			}
			else
				return (free_commands(commands), NULL);
		}
		else if (token->type == TOKEN_HEREDOC)
		{
			if (token->next && token->next->type == TOKEN_WORD)
			{
				current_cmd->heredoc_delimiter = ft_strdup(token->next->value);
				token = token->next->next;
			}
			else
				return (free_commands(commands), NULL);
		}
		else if (token->type == TOKEN_PIPE)
		{
			current_cmd->next = create_command();
			current_cmd = current_cmd->next;
			token = token->next;
		}
		else
		{
			// Se for tipo desconhecido, apenas avançamos
			token = token->next;
		}
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

//apagar apenas para debug dos comandos
void debug_print_commands(t_command *commands)
{
	t_command *cmd;
	int i;
	int cmd_num;

	cmd = commands;
	cmd_num = 1;
	while (cmd)
	{
		printf("\n==== Comando %d ====\n", cmd_num++);
		if (cmd->args)
		{
			printf("Args:\n");
			i = 0;
			while (cmd->args[i])
			{
				printf("  [%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		else
			printf("Args: (nenhum)\n");

		printf("Input file: %s\n", cmd->input_file ? cmd->input_file : "(nenhum)");
		printf("Output file: %s\n", cmd->output_file ? cmd->output_file : "(nenhum)");
		printf("Append output? %s\n", cmd->append_output ? "Sim" : "Não");
		printf("Heredoc delimiter: %s\n", cmd->heredoc_delimiter ? cmd->heredoc_delimiter : "(nenhum)");

		cmd = cmd->next;
	}
}
