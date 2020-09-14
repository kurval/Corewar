/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:52:34 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/05 16:52:38 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	handle_invalid_label(t_arg *arg, char *label_name)
{
	char	*msg;
	char	**strs;

	if (!(strs = (char **)malloc(sizeof(char *) * 7)) ||
	!(strs[0] = ft_strdup(label_name)) ||
	!(strs[1] = ft_strdup("while attempting to dereference token")))
		handle_error(MALLOC_ERROR);
	strs[2] = pad_nbr(arg->cursor->row, 3);
	strs[3] = pad_nbr(arg->cursor->col + 1, 3);
	if (!(strs[4] = ft_strdup(token_type_str(arg->type))) ||
	!(strs[5] = ft_strdup(arg->content)))
		handle_error(MALLOC_ERROR);
	strs[6] = NULL;
	msg = add_strs_to_str("No such label %s %s [TOKEN][%s:%s] %s \"%s\"", strs);
	del_array(strs);
	handle_error_free_msg(msg);
}

void	handle_invalid_argument(int err_type, char *instr_name, int row,
t_token *token)
{
	char	*msg;
	char	**strs;

	if (!(strs = (char **)malloc(sizeof(char *) * 4)) ||
		!(strs[0] = ft_itoa(row)) ||
		!(strs[1] = ft_strdup(instr_name)))
		handle_error(MALLOC_ERROR);
	msg = NULL;
	if (err_type == INVALID_COUNT)
	{
		strs[2] = NULL;
		msg = add_strs_to_str("row %s: Invalid arg count for \"%s\"", strs);
	}
	else if (err_type == INVALID_TYPE)
	{
		strs[2] = (token ? ft_strdup(token_type_str(token->type)) :
		ft_strdup("END"));
		if (!strs[2])
			handle_error(MALLOC_ERROR);
		strs[3] = NULL;
		msg = add_strs_to_str("row %s: Invalid argument for \"%s\" (type %s)",
		strs);
	}
	del_array(strs);
	handle_error_free_msg(msg);
}

void	handle_error_msg(int error, t_token *token)
{
	char	*msg;
	char	**strs;

	if (!token)
	{
		handle_error("Syntax error - unexpected end of input");
		if (g_flags & flag_e)
			return ;
	}
	if (!(strs = (char **)malloc(sizeof(char *) * 6)) ||
	!(strs[0] = ft_strdup((overlap(SYNTAX_ERROR, error) ? "Syntax error" :
	"Invalid instruction"))))
		handle_error(MALLOC_ERROR);
	strs[1] = pad_nbr(token->cursor->row, 3);
	strs[2] = pad_nbr(token->cursor->col + 1, 3);
	if (!(strs[3] = ft_strdup(token_type_str(token->type))) ||
	!(strs[4] = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	strs[5] = NULL;
	if (token->type != endline)
		msg = add_strs_to_str("%s at token [TOKEN][%s:%s] %s \"%s\"", strs);
	else
		msg = add_strs_to_str("%s at token [TOKEN][%s:%s] %s", strs);
	del_array(strs);
	handle_error_free_msg(msg);
}

void	lexical_error(t_cursor cursor)
{
	char	**cursor_str;
	char	*msg;

	if (!(cursor_str = (char **)malloc(sizeof(char *) * 3)))
		handle_error(MALLOC_ERROR);
	cursor_str[0] = ft_itoa(cursor.row);
	cursor_str[1] = ft_itoa(cursor.col + 1);
	cursor_str[2] = NULL;
	msg = add_strs_to_str("Lexical error at [%s:%s]", cursor_str);
	del_array(cursor_str);
	handle_error_free_msg(msg);
}
