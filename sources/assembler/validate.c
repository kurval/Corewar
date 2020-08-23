/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:19:16 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/05 13:19:18 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		validate_number(char *line, int start, t_cursor cursor)
{
	int i;

	i = start;
	i = (line[i] == '-' ? start + 1 : start);
	if (!ft_isdigit(line[i]))
		lexical_error(cursor);
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

int		validate_cmd_str(char *line, t_cursor cursor)
{
	size_t name_cmdlen;
	size_t comment_cmdlen;

	name_cmdlen = ft_strlen(NAME_CMD_STRING);
	comment_cmdlen = ft_strlen(COMMENT_CMD_STRING);
	if (ft_strncmp(&line[cursor.col], NAME_CMD_STRING, name_cmdlen) == 0)
		return (cursor.col + name_cmdlen);
	if (ft_strncmp(&line[cursor.col], COMMENT_CMD_STRING, comment_cmdlen) == 0)
		return (cursor.col + comment_cmdlen);
	return (0);
}

int		is_valid_char(char c)
{
	if (ft_strchr(LABEL_CHARS, c))
		return (1);
	return (0);
}

void	validate_characters(char *line, int col, int row, int *end_point)
{
	t_cursor cursor;

	cursor.col = col;
	cursor.row = row;
	while (line[cursor.col] && (cursor.col < *end_point || *end_point == -1))
	{
		if (is_comment_char(line[cursor.col]) || line[cursor.col] == '\n')
			break ;
		if (!is_valid_char(line[cursor.col]))
		{
			if (validate_cmd_str(line, cursor))
			{
				*end_point = cursor.col;
				break ;
			}
			else
				lexical_error(cursor);
		}
		cursor.col++;
	}
}
