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

int				is_valid_char(char c)
{
	if (ft_strchr(LABEL_CHARS, c))
		return (1);
	return (0);
}

int				skip_whitespaces(char *line, int i)
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
