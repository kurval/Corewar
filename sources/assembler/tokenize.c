#include "asm.h"

t_token			*make_token(char *line, t_cursor *cursor)
{
	t_token		*token = NULL;

	cursor->col++;
	return (token);
}

t_token			*tokenize(char *line, t_cursor cursor)
{
	t_token *token;
	t_token *head;
	int test;

	head = NULL;
	while (line[cursor.col])
	{
		cursor.col = skip_whitespaces(line, cursor.col);
		if (is_valid_char(line[cursor.col]))
		{
			if (!head)
			{
				token = make_token(line, &cursor);
				head = token;
			}
			else
			{
				token->next = make_token(line, &cursor);
				token = token->next;
			}
		}
	}
	return (head);
}