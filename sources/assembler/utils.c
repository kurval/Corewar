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

int		skip_whitespaces(char *line, int i)
{
	while (line[i])
	{
		if (!ft_strchr(" \t\r\v\f", line[i]))
			return (i);
		i++;
	}
	return (i);
}

int		ft_isnum(char *str)
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

int		count_string_chars(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	return (count);
}

char	*copy_string_content(char *string)
{
	int		len;
	int		start;
	char	*copy;

	start = 0;
	len = ft_strlen(string);
	if (string[len - 1] == '"')
		len--;
	if (string[0] == '"')
	{
		len--;
		start = 1;
	}
	copy = ft_strsub(string, start, len);
	return (copy);
}
