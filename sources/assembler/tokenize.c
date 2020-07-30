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

int				skip_first_direct_and_label(char *line, t_cursor cursor,
int	*has_label_or_direct)
{
	int i;

	*has_label_or_direct = 0;
	i = cursor.col;
	if (line[i] == DIRECT_CHAR)
	{
		i++;
		if (line[i] == LABEL_CHAR)
		{
			*has_label_or_direct = LABEL;
			i++;
		}
		else if ((line[i] == '-' && ft_isdigit(line[i + 1])) ||
		ft_isdigit(line[i]))
		{
			*has_label_or_direct = DIRECT;
			i++;
		}
		else
			lexical_error_tmp(cursor);
	}
	else if (line[i] == LABEL_CHAR)
	{
		*has_label_or_direct = LABEL;
		i++;
	}
	return (i);
}

int		skip_number(char *line, int start)
{
	int i;

	i = start;
	i = (line[i] == '-' ? start + 1 : start);
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

/*
**	Checks if there are lexical errors in the current token bit,
**	and sets token end (the index of the limiting character).
**
**	Example 1:
**
**	% : l a b e l :			0 - cursor.col	2 - token_content_start
**	0 1 2 3 4 5 6 7			7 - *token_end
**
**	Example 2;
**	l a b e l :				0 - cursor.col	0 - token_content_start
**	0 1 2 3 4 5 6 7			6 - *token_end
*/

void			check_for_lexical_error(char *line, t_cursor cursor,
int *token_end, char *edge_chars)
{
	int		token_content_start;
	int		has_label_or_direct;

	if (line[cursor.col] == SEPARATOR_CHAR)
	{
		token_content_start = cursor.col;
		*token_end = cursor.col + 1;
	}
	else
	{
		token_content_start = skip_first_direct_and_label(line, cursor, &has_label_or_direct);
		if (has_label_or_direct == DIRECT) //ADD A CASE IF LINE STARTING AT THIS POINT IS A NUMBER SKIP IT
			*token_end = skip_number(line, token_content_start);
		else
		{
		*token_end = find_first_char(line, token_content_start, edge_chars);
		validate_characters(line, token_content_start, cursor.row, *token_end);
		if (!has_label_or_direct && line[*token_end] == LABEL_CHAR)
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
