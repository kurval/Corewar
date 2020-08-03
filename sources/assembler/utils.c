/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:16:59 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:03 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	skip_whitespaces(char *line, int i)
{
	char whitespaces[] = " \t\r\v\f";

	while (line[i])
	{
		if (!ft_strchr(whitespaces, line[i]))
			return (i);
		i++;
	}
	return (i);
}

int	ft_isnum(char *str)
{
	int	i;

	i = (str[0] == '-' ? 1 : 0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}
