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

int				determine_token_type(char *content, int content_len)
{
	if (content[0] == DIRECT_CHAR)
		return (content[1] == LABEL_CHAR ? DIRECT_LABEL : DIRECT);
	else if (content[0] == LABEL_CHAR)
		return (INDIRECT_LABEL);
	else if (ft_strequ(content, NAME_CMD_STRING))
		return (COMMAND_NAME);
	else if (ft_strequ(content, COMMENT_CMD_STRING))
		return (COMMAND_COMMENT);
	else if (content[0] == '"')
		return (STRING);
	else if (content[0] == 'r' && content_len > 1 && content_len < 4 &&
	ft_isdigit(content[1]) && (ft_isdigit(content[2]) || !content[2]))
		return (REGISTER);
	else if (content[0] == SEPARATOR_CHAR)
		return (SEPARATOR);
	else if (content[content_len - 1] == LABEL_CHAR)
		return (LABEL);
	else if (ft_isnum(content))
		return (INDIRECT);
	else
		return (INSTRUCTION);
}

t_token			*make_token(char *line, t_cursor *cursor, int end)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->next = NULL;
	if (end != -1)
		token->content = ft_strsub(line, cursor->col, end - cursor->col);
	else
		token->content = ft_strdup(&line[cursor->col]);
	token->cursor = copy_cursor(*cursor);
	token->type = determine_token_type(token->content, end - cursor->col);
	cursor->col = end;
	return (token);
}

t_token			*make_endline_token(t_token *head, t_token *token,
t_cursor cursor, char *line)
{
	t_token *endline;

	while (line[cursor.col] && line[cursor.col] != '\n')
		cursor.col++;
	if (!line[cursor.col])
		return (head);
	endline = (t_token *)malloc(sizeof(t_token));
	endline->next = NULL;
	endline->content = ft_strdup("\n");
	endline->type = ENDLINE;
	endline->cursor = copy_cursor(cursor);
	if (!head)
		head = endline;
	else
		token->next = endline;
	return (head);
}

static int		find_token_start(char *line, t_cursor *cursor)
{
	cursor->col = skip_whitespaces(line, cursor->col);
	if (line[cursor->col] == '\n' || line[cursor->col] == COMMENT_CHAR ||
	!line[cursor->col])
		return (0);
	else
		return (1);
}

t_token			*tokenize(char *line, t_cursor cursor, char *edge_chars)
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
