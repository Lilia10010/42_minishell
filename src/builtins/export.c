/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: microbiana <microbiana@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:05:39 by meandrad          #+#    #+#             */
/*   Updated: 2025/07/29 18:04:31 by microbiana       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

int builtin_export(char **args, t_context *ctx)
{
	//todo este codigo é só de debug, retirar tudinho inho 
	(void)ctx;
	int i = 0;
	while (args[i])
	{
		printf("export %s\n", args[i]);
		++i;
	}
	return (0);
}
