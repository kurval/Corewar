/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:19 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:21 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Checks that champion info is not set multiple times,
**	and that info is set before other types of tokens.
*/

static void	check_statement_order(t_token *token, t_champ *champ)
{
	if (token && token->type != endline)
	{
		if (overlap(token->type, cmd_str))
		{
			if (token->type == command_name && champ->name)
				handle_error_msg(SYNTAX_ERROR, token);
			if (token->type == command_comment && champ->comment)
				handle_error_msg(SYNTAX_ERROR, token);
		}
		else if (!champ->done)
		{
			handle_error_msg(SYNTAX_ERROR, token);
			champ->done = DEBUG_AFTER_MISSING_INFO;
		}
	}
}

static int	asm_gnl(const int fd, char **line, int *row)
{
	int			ret;
	char		buff[BUFF_SIZE + 1];
	static char	*s[FD_MAX];
	int			value;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		value = store_line(buff, s, &ret, fd);
		if (value == -1)
			return (-1);
		else if (value == 0)
			break ;
	}
	return (ret_value(&s[fd], line, ret, row));
}

static void	init_champ(t_champ *champ)
{
	champ->name = NULL;
	champ->comment = NULL;
	champ->labels = NULL;
	champ->stmts = NULL;
	champ->done = 0;
}

static char	*create_edge_chars(void)
{
	char *chars;

	if (!(chars = (char *)malloc(sizeof(char) * 13)))
		handle_error(MALLOC_ERROR);
	chars = ft_strcpy(chars, " \t\n\r\v\f");
	chars[6] = LABEL_CHAR;
	chars[7] = COMMENT_CHAR;
	chars[8] = SEPARATOR_CHAR;
	chars[9] = DIRECT_CHAR;
	chars[10] = '-';
	chars[11] = ALT_COMMENT_CHAR;
	chars[12] = '\0';
	return (chars);
}

void		parse_file(int fd, t_asm *assembler)
{
	char		*line;
	t_cursor	cursor;
	char		*edge_chars;

	cursor.row = 1;
	edge_chars = create_edge_chars();
	init_champ(&assembler->champ);
	while (asm_gnl(fd, &line, &cursor.row) && line)
	{
		cursor.col = 0;
		assembler->tokens = tokenize(line, cursor, edge_chars);
		check_token_order(assembler->tokens);
		check_token_validity(assembler->tokens, assembler->op);
		check_statement_order(assembler->tokens, &assembler->champ);
		ft_strdel(&line);
		set_champ(&assembler->champ, assembler->tokens);
		fix_label_place(&assembler->champ);
		free_tokens(&assembler->tokens);
		cursor.row++;
	}
	free(edge_chars);
	if (assembler->champ.done != 1)
		handle_error("Champion name or comment missing");
	check_str_len(assembler->champ.name, assembler->champ.comment);
	labels_to_rel_adrs(assembler->champ.labels, assembler->champ.stmts);
}
