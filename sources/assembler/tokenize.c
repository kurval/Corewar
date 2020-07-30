/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:26 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:27 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token			*make_token(char *line, t_cursor *cursor, int token_end)
{
	t_token	*token = NULL;

	cursor->col = token_end;
	return (token);
}

char			*create_edge_chars(void)
{
	char *chars;

	chars = (char *)malloc(sizeof(char) * 10);
	chars = ft_strdup(" \t\n\r\v\f");
	chars[6] = LABEL_CHAR;
	chars[7] = COMMENT_CHAR;
	chars[8] = SEPARATOR_CHAR;
	chars[9] = DIRECT_CHAR;
	chars[10] = '\0';
	return (chars);
}

int				skip_first_direct_and_label(char *line, t_cursor cursor,
int	*label_usable)
{
	int i;

	*label_usable = 1;
	i = cursor.col;
	if (line[i] == DIRECT_CHAR)
		i++;
	if (line[i] == LABEL_CHAR)
		i++;
	if (i != cursor.col)
		*label_usable = 0;
	return (i);
}

/*
**	Checks if there are lexical errors in the current token bit,
**	and sets token end (the index of the limiting character).
**
**	Example:
**
**	% : l a b e l ,			0 - cursor.col	2 - token_content_start
**	0 1 2 3 4 5 6 7			7 - *token_end
*/

void			check_for_lexical_error(char *line, t_cursor cursor,
int *token_end, char *edge_chars)
{
	int		token_content_start;
	int		is_label_usable;

	if (line[cursor.col] == SEPARATOR_CHAR)
	{
		token_content_start = cursor.col;
		*token_end = cursor.col + 1;
	}
	else
	{
		token_content_start = skip_first_direct_and_label(line, cursor, &is_label_usable);
		*token_end = find_first_char(line, token_content_start, edge_chars);
		validate_characters(line, token_content_start, cursor.row, *token_end);
		if (is_label_usable && line[*token_end] == LABEL_CHAR &&
		ft_strchr(edge_chars, line[*token_end + 1]))
		{
			*token_end = *token_end + 1;
		}
	}
}

t_token			*tokenize(char *line, t_cursor cursor)
{
	t_token *token;
	t_token *head;
	char	*edge_chars;
	int		token_end;
	int		token_start;

	head = NULL;
	edge_chars = create_edge_chars();
	while (line[cursor.col])
	{
		if (line[cursor.col] == '\n')
			break ;
		cursor.col = skip_whitespaces(line, cursor.col);
		check_for_lexical_error(line, cursor, &token_end, edge_chars);
		write(1, &line[cursor.col], token_end - cursor.col);
		ft_printf(" <%d>\n", token_end - cursor.col);
		if (!head)
		{
			token = make_token(line, &cursor, token_end);
			head = token;
		}
		else
		{
			token->next = make_token(line, &cursor, token_end);
			token = token->next;
		}
	}
	return (head);
}
