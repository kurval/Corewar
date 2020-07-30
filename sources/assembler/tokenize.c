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

t_token			*make_token(char *line, t_cursor *cursor)
{
	t_token	*token = NULL;

	cursor->col++;
	return (token);
}

t_token			*tokenize(char *line, t_cursor cursor)
{
	t_token *token;
	t_token *head;

	head = NULL;
	while (line[cursor.col])
	{
		cursor.col = skip_whitespaces(line, cursor.col);
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
	return (head);
}
