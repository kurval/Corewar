/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:26 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:27 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			free_tokens(t_token **tokens)
{
	t_token *current;
	t_token *next;

	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current->cursor);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

t_token			*make_endline_token(t_token *head, t_token *token,
t_cursor cursor, char *line)
{
	t_token *end_token;

	while (line[cursor.col] && line[cursor.col] != '\n')
		cursor.col++;
	if (!line[cursor.col] && head)
		return (head);
	if (!(end_token = (t_token *)malloc(sizeof(t_token))))
		handle_error(MALLOC_ERROR);
	end_token->next = NULL;
	if (!(end_token->content = ft_strdup("\n")))
		handle_error(MALLOC_ERROR);
	end_token->type = endline;
	end_token->cursor = copy_cursor(cursor);
	if (!head)
		head = end_token;
	else
		token->next = end_token;
	return (head);
}

static int		is_num(char *str)
{
	int	i;

	i = (str[0] == '-' ? 1 : 0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

static t_type	determine_token_type(char *content, int content_len)
{
	if (content[0] == DIRECT_CHAR)
		return (content[1] == LABEL_CHAR ? direct_label : direct);
	else if (content[0] == LABEL_CHAR)
		return (indirect_label);
	else if (ft_strequ(content, NAME_CMD_STRING))
		return (command_name);
	else if (ft_strequ(content, COMMENT_CMD_STRING))
		return (command_comment);
	else if (content[0] == '"')
		return (string);
	else if (content[0] == 'r' && content_len > 1 && content_len < 4 &&
	ft_isdigit(content[1]) && (ft_isdigit(content[2]) || !content[2]))
		return (reg);
	else if (content[0] == SEPARATOR_CHAR)
		return (separator);
	else if (content[content_len - 1] == LABEL_CHAR)
		return (label);
	else if (is_num(content))
		return (indirect);
	else
		return (instruction);
}

t_token			*make_token(char *line, t_cursor *cursor, int end)
{
	t_token	*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		handle_error(MALLOC_ERROR);
	token->next = NULL;
	if (end != -1)
		token->content = ft_strsub(line, cursor->col, end - cursor->col);
	else
		token->content = ft_strdup(&line[cursor->col]);
	if (!token->content)
		handle_error(MALLOC_ERROR);
	token->cursor = copy_cursor(*cursor);
	token->type = determine_token_type(token->content, end - cursor->col);
	cursor->col = end;
	return (token);
}
