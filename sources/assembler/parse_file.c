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
		ft_printf("%s\n", line);
	}
}