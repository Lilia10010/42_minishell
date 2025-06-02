/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:37:37 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/01 22:41:38 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void process_input(char *input)
{
	printf("%s\n", input);
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char *input;
	
    (void)argc;
    (void)argv;

	init_shell(&shell, envp);

	while (1)
	{
		input = readline("minishell$");
		if (!input)
		{
			printf("exit => ctr + d\n");
			break ;
		}
		if (!*input)
		{
			printf("entra aqui quando não é digitado nada\n");
			free(input);
			continue;
		}
		add_history(input);
		process_input(input);
		free(input);
	}
    return (0);
}