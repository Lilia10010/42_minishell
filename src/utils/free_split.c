/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaula-n <lpaula-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:42:48 by lpaula-n          #+#    #+#             */
/*   Updated: 2025/08/10 23:43:08 by lpaula-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_split(char **split)
{
	int i;

	i = 0;
	if (!split)
		return  ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}