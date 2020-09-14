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

static int	skip_whitespaces(char *line, int i)
{
	while (line[i])
	{
		if (!ft_strchr(" \t\r\v\f", line[i]))
			return (i);
		i++;
	}
	return (i);
}

static int	find_token_start(char *line, t_cursor *cursor)
{
	cursor->col = skip_whitespaces(line, cursor->col);
	if (line[cursor->col] == '\n' || is_comment_char(line[cursor->col]) ||
	!line[cursor->col])
		return (0);
	else
		return (1);
}

t_token		*tokenize(char *line, t_cursor cursor, char *edge_chars)
{
	t_token *token;
	t_token *head;
	int		token_end;
	int		token_start;

	head = NULL;
	while (line[cursor.col])
	{
		if (!find_token_start(line, &cursor))
			break ;
		if (!(token_end = validate_cmd_str(line, cursor)))
			check_for_lexical_error(line, cursor, &token_end, edge_chars);
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
	return (make_endline_token(head, token, cursor, line));
}
