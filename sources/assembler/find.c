/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:16:46 by jmetelin          #+#    #+#             */
/*   Updated: 2020/07/29 15:16:52 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	find_last_str(char *haystack, int start, char *needle)
{
	int	needle_len;
	int	i;
	int	j;

	needle_len = ft_strlen(needle);
	i = start;
	while (haystack && i >= 0)
	{
		j = needle_len - 1;
		while (i >= 0 && needle && j >= 0 && haystack[i] == needle[j])
		{
			i--;
			j--;
		}
		if (j == -1)
			return (i + 1);
		i--;
	}
	return (-1);
}

int	find_first_str(char *haystack, int start, char *needle)
{
	int needle_start;
	int	needle_len;
	int	i;
	int	j;

	needle_len = ft_strlen(needle);
	i = start;
	while (haystack && haystack[i])
	{
		needle_start = i;
		j = 0;
		while (haystack[i] && needle && needle[j] && haystack[i] == needle[j])
		{
			i++;
			j++;
		}
		if (j == needle_len)
			return (needle_start);
		if (haystack[i])
			i++;
	}
	return (-1);
}

int	find_last_char(char *str, int start, char *chars)
{
	int	i;
	int	j;

	i = start;
	while (str && i >= 0)
	{
		j = 0;
		while (chars && chars[j])
		{
			if (str[i] == chars[j])
				return (i);
			j++;
		}
		i--;
	}
	return (-1);
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
