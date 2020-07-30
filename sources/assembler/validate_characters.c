#include "asm.h"

void	lexical_error(t_cursor cursor)
{
	ft_printf("Lexical error [%d:%d]\n", cursor.row, cursor.col + 1);
	exit(1);
}

int	is_valid_char(char c)
{
	if (ft_strchr(LABEL_CHARS, c))
		return (1);
	return (0);
}

void	validate_characters(char *line, t_cursor cursor)
{
	cursor.col = 0;
	while (line[cursor.col] && 
	line[cursor.col] != COMMENT_CHAR && line[cursor.col] != '\n')
	{
		cursor.col = skip_whitespaces(line, cursor.col);
		cursor.col = skip_valid_chars(line, cursor.col);
		if (line[cursor.col] == COMMENT_CHAR || line[cursor.col] == '\n')
			break ;
		if (!is_valid_char(line[cursor.col]))
			lexical_error(cursor);
		cursor.col++;
	}
}
