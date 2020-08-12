/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_lexical_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:19:08 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/05 13:19:10 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	case_label(int *i, int *has_label_or_direct, char *line,
t_cursor cursor)
{
	if (!is_valid_char(line[*i + 1]))
		lexical_error(cursor);
	*has_label_or_direct = LABEL;
	*i = *i + 1;
}

static int	check_label_or_dir(char *line, t_cursor cursor,
int *token_content_start)
{
	int i;
	int	has_label_or_direct;

	has_label_or_direct = 0;
	i = cursor.col;
	if (line[i] == DIRECT_CHAR)
	{
		i++;
		if (line[i] == LABEL_CHAR)
			case_label(&i, &has_label_or_direct, line, cursor);
		else if ((line[i] == '-' && ft_isdigit(line[i + 1])) ||
		ft_isdigit(line[i]))
			has_label_or_direct = DIRECT;
		else
			lexical_error(cursor);
	}
	else if (line[i] == LABEL_CHAR)
		case_label(&i, &has_label_or_direct, line, cursor);
	*token_content_start = i;
	return (has_label_or_direct);
}

int			check_string_or_separator(char *line, t_cursor cursor,
int *token_end)
{
	if (line[cursor.col] == SEPARATOR_CHAR)
	{
		*token_end = cursor.col + 1;
		return (1);
	}
	else if (line[cursor.col] == '"')
	{
		*token_end = cursor.col + 1;
		while (line[*token_end])
		{
			*token_end = *token_end + 1;
			if (line[*token_end - 1] == '"')
				break ;
		}
		return (1);
	}
	return (0);
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

void		check_for_lexical_error(char *line, t_cursor cursor,
int *token_end, char *edge_chars)
{
	int		token_content_start;
	int		label_or_dir;

	if (!check_string_or_separator(line, cursor, token_end))
	{
		label_or_dir = check_label_or_dir(line, cursor, &token_content_start);
		if (label_or_dir == DIRECT || line[token_content_start] == '-')
			*token_end = validate_number(line, token_content_start, cursor);
		else
		{
			*token_end = find_first_char(line, token_content_start, edge_chars);
			if (*token_end == -1)
				*token_end = ft_strlen(line);
			validate_characters(line, token_content_start, cursor.row,
			token_end);
			if (!label_or_dir && line[*token_end] == LABEL_CHAR)
				*token_end = *token_end + 1;
		}
	}
}
