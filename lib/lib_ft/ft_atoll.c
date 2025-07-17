/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:30:05 by meandrad          #+#    #+#             */
/*   Updated: 2025/07/14 20:37:40 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *s)
{
	long long	result;
	int			i;
	int			flag;

	result = 0;
	flag = 1;
	i = 0;
	while (ft_isspace(s[i]) == 1)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			flag = -1;
		i++;
	}
	while (ft_isdigit(s[i]) == 1)
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * flag);
}

