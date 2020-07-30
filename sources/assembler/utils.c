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

int				skip_valid_chars(char *line, int i)
{
	while (line[i] && (line[i] == LABEL_CHAR ||
	line[i] == SEPARATOR_CHAR || line[i] == DIRECT_CHAR ||
	line[i] == '"' || line[i] == '-'))
	{
		
		if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '\n' && line[i] != COMMENT_CHAR &&
			line[i] != '"')
				i++;
		}
		if (!line[i])
			break ;
		i++;
	}
	return (i);
}