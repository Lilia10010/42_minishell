/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:37:37 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/03 22:54:35 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *input;
	t_token *tokens;
	t_command *command;


	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		//history deve excluir o histórico vindo do heredoc
		if (*input)
			add_history(input);
		
		tokens = lexer_tokenize(input);
		command = parse_tokens(tokens);
		execute_command(command);

		//dar free em tokens - command - input
		//free()
	}
	return (0);
}

//1 - readline
//2 - lexer + parse
// tudo ok
//3 - executor