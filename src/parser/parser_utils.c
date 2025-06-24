/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:54:56 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/06/23 21:04:17 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
# include "parser.h"
#include "minishell.h"

t_token	*collect_args(t_token *start, char ***args_out)
{
	t_token *token;
	char **args;
	int count;
	int i;

	count = count_word_tokens(start);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);

	i = 0;
	token = start;
	while (token && token->type == TOKEN_WORD)
	{
		args[i] = ft_strdup(token->value);
		i++;
		token = token->next;
	}
	args[i] = NULL;
	*args_out = args;
	return (token);
}
