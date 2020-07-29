/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_first_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:16:46 by jmetelin          #+#    #+#             */
/*   Updated: 2020/07/29 15:16:52 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	find_last_char(char *str, int start, char *chars)
{
	int	c;
	int	i;
	int	j;

	c = -1;
	i = start;
	while (str && str[i])
	{
		j = 0;
		while (chars && chars[j])
		{
			if (str[i] == chars[j])
				c = i;
			j++;
		}
		i++;
	}
	return (c);
}

int	find_first_char(char *str, int start, char *chars)
{
	int	i;
	int	j;

	i = start;
	while (str && str[i])
	{
		j = 0;
		while (chars && chars[j])
		{
			if (str[i] == chars[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
