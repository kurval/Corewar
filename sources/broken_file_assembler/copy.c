/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:01:39 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/12 14:01:40 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*copy_string_content(char *string)
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

t_cursor	*copy_cursor(t_cursor cursor)
{
	t_cursor *new;

	if (!(new = (t_cursor *)malloc(sizeof(t_cursor))))
		handle_error(MALLOC_ERROR);
	new->col = cursor.col;
	new->row = cursor.row;
	return (new);
}
