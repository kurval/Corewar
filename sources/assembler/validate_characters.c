#include "asm.h"

/*
** Temporary lexical error for testing
*/

void	lexical_error_tmp(t_cursor cursor)
{
	ft_printf("Lexical error [%d:%d] (this message is temporary)\n", cursor.row, cursor.col + 1);
	exit(1);
}

int	is_valid_char(char c)
{
	if (ft_strchr(LABEL_CHARS, c))
		return (1);
	return (0);
}

void	validate_characters(char *line, int col, int row, int end_point)
{
	t_cursor cursor;

	cursor.col = col;
	cursor.row = row;
	while (line[cursor.col] && cursor.col < end_point)
	{
		if (line[cursor.col] == COMMENT_CHAR || line[cursor.col] == '\n')
			break ;
		if (line[cursor.col] == '-' && ft_isdigit(line[cursor.col + 1]))
			cursor.col++;
		if (!is_valid_char(line[cursor.col]))
			lexical_error_tmp(cursor);
		cursor.col++;
	}
}
