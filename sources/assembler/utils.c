#include "asm.h"

int				is_valid_char(char c)
{
	if (ft_strchr(LABEL_CHARS, c))
		return (1);
	return (0);
}

int				skip_whitespaces(char *line, int i)
{
	char whitespaces[] = " \t\r\v\f";

	while (line[i])
	{
		if (!ft_strchr(whitespaces, line[i]))
			return (i);
		i++;
	}
	return (i);
}