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
#include <fcntl.h>

void			print_tokens(t_token *tokens)
{
	t_token *current;

	while (current)
	{

		current = current->next;
	}
}

void			parse_file(int fd)
{
	char		*line;
	t_cursor	cursor;
	t_token		*tokens;
	t_statement *statement;
	
	fd = open("test", O_RDONLY);
	cursor.row = 1;
	while (get_next_line(fd, &line))
	{
		cursor.col = 0;
		validate_characters(line, cursor);
		tokens = tokenize(line, cursor);
		//print_tokens(tokens);
		cursor.row++;
	}
	close(fd);
}
