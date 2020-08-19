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

#include "../../includes/asm.h"

char			*create_edge_chars(void)
{
	char *chars;

	chars = (char *)malloc(sizeof(char) * 12);
	chars = ft_strcpy(chars, " \t\n\r\v\f");
	chars[6] = LABEL_CHAR;
	chars[7] = COMMENT_CHAR;
	chars[8] = SEPARATOR_CHAR;
	chars[9] = DIRECT_CHAR;
	chars[10] = '-';
	chars[11] = '\0';
	return (chars);
}

char			*token_type_str(int type)
{
	if (type == REGISTER)
		return ("REGISTER");
	if (type == DIRECT)
		return ("DIRECT");
	if (type == INDIRECT)
		return ("INDIRECT");
	if (type == INSTRUCTION)
		return ("INSTRUCTION");
	if (type == LABEL)
		return ("LABEL");
	if (type == SEPARATOR)
		return ("SEPARATOR");
	if (type == STRING)
		return ("STRING");
	if (overlap(type, CMD_STR))
		return (type == COMMAND_NAME ? "COMMAND_NAME" : "COMMAND_COMMENT");
	if (type == DIRECT_LABEL)
		return ("DIRECT_LABEL");
	if (type == INDIRECT_LABEL)
		return ("INDIRECT_LABEL");
	if (type == INDIRECT)
		return ("INDIRECT");
	if (type == ENDLINE)
		return ("ENDLINE");
	return (NULL);
}

void			print_tokens(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		ft_printf("Content: %s\nType: %s\nLoc: [%d:%d]\n\n", current->content,
		token_type_str(current->type), current->cursor->row,
		current->cursor->col);
		current = current->next;
	}
	ft_putchar('\n');
}

void			free_tokens(t_token *tokens)
{
	t_token *current;
	t_token *next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current->cursor);
		free(current);
		current = next;
	}
}

void			print_labels(t_label *labels)
{
	t_label *curr;

	curr = labels;
	while (curr)
	{
		ft_printf("label %s place %d\n", curr->name, curr->place);
		curr = curr->next;
	}
}

void			parse_file(int fd, t_asm *assembler)
{
	char		*line;
	t_cursor	cursor;
	char		*edge_chars;

	cursor.row = 1;
	edge_chars = create_edge_chars();
	init_champ(&assembler->champ);
	while (asm_gnl(fd, &line))
	{
		cursor.col = 0;
		assembler->tokens = tokenize(line, cursor, edge_chars);
		//print_tokens(assembler->tokens);
		check_token_order(assembler->tokens);
		check_token_validity(assembler->tokens, assembler->op);
		check_statement_order(assembler->tokens, &assembler->champ);
		ft_strdel(&line);
		set_champ(&assembler->champ, assembler->tokens);
		free_tokens(assembler->tokens);
		assembler->tokens = NULL;
		cursor.row++;
	}
	free(edge_chars);
	//print_labels(assembler->champ.labels);
	labels_to_rel_adrs(assembler->champ.labels, assembler->champ.stmts);
}
