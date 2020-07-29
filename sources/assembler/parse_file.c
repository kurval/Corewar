/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:19 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:21 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			parse_file(int fd)
{
	char	*line;
	t_cursor	cursor; //Our current place in the file (row/col)
	t_token		*tokens;
	t_statement *statement;

	cursor.row = 0;
	while (get_next_line(fd, &line))
	{
		cursor.col = 0;
		tokens = tokenize(line, cursor);
		cursor.row++;
	}
}
