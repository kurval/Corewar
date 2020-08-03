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

char			*create_edge_chars(void)
{
	char *chars;

	chars = (char *)malloc(sizeof(char) * 11);
	chars = ft_strdup(" \t\n\r\v\f");
	chars[6] = LABEL_CHAR;
	chars[7] = COMMENT_CHAR;
	chars[8] = SEPARATOR_CHAR;
	chars[9] = DIRECT_CHAR;
	chars[10] = '-';
	chars[11] = '\0';
	return (chars);
}

char			*token_type_str(int type)
{
	if (type == REGISTER)
		return ("REGISTER");
	if (type == DIRECT)
		return ("DIRECT");
	if (type == INDIRECT)
		return ("INDIRECT");
	if (type == INSTRUCTION)
		return ("INSTRUCTION");
	if (type == LABEL)
		return ("LABEL");
	if (type == SEPARATOR)
		return ("SEPARATOR");
	if (type == STRING)
		return ("STRING");
	if (type == CMD_STR)
		return ("CMD_STR");
	if (type == DIRECT_LABEL)
		return ("DIRECT_LABEL");
	if (type == INDIRECT_LABEL)
		return ("INDIRECT_LABEL");
	if (type == INDIRECT)
		return ("INDIRECT");
	if (type == ENDLINE)
		return ("ENDLINE");
	return (NULL);
}

void			print_tokens(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		ft_printf("Content: %s\nType: %s\nLoc: [%d:%d]\n\n", current->content,
		token_type_str(current->type), current->cursor->row,
		current->cursor->col);
		current = current->next;
	}
	ft_putchar('\n');
}

void			parse_file(int fd)
{
	char		*line;
	t_cursor	cursor;
	t_token		*tokens;
	t_statement *statement;
	char		*tmp_line; //This will be deleted when gnl is fixed
	char		*edge_chars;

	cursor.row = 1;
	edge_chars = create_edge_chars();
	while (get_next_line(fd, &line))
	{
		cursor.col = 0;
		tmp_line = ft_strjoin(line, "\n"); //this is temporary until gnl is fixed
		tokens = tokenize(tmp_line, cursor, edge_chars);
		free(tmp_line);
		free(line);
		print_tokens(tokens);
		cursor.row++;
	}
	free(edge_chars);
}
