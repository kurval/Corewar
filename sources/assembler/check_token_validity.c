/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_validity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:52:34 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/05 16:52:38 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			handle_invalid_argument(int err_type, char *instr_name,
int row, t_token *token)
{
	char	*msg;
	char	**strs;

	if (!(strs = (char **)malloc(sizeof(char *) * 4)) ||
		!(strs[0] = ft_itoa(row)) ||
		!(strs[1] = ft_strdup(instr_name)))
		handle_error(MALLOC_ERROR);
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

static void		check_instr_validity(t_token *token, t_op **op)
{
	while (*op && !ft_strequ((*op)->instr_name, token->content))
		*op = (*op)->next;
	if (!(*op))
		handle_error_msg(INVALID_INSTR, token);
}

/*
** Check_token_validity
** 1. Checks that the instruction is valid and has a valid amount of valid
**    arguments
** 2. Prints the correct error msg to STDERR
*/

void			check_token_validity(t_token *token, t_op *op)
{
	int		argc;
	char	*instr;
	int		row_nbr;

	if (token && token->type == label)
		token = token->next;
	if (token && token->type == instruction)
	{
		row_nbr = token->cursor->row;
		instr = token->content;
		check_instr_validity(token, &op);
		token = token->next;
		argc = 0;
		while (token && (overlap((T_REG | T_DIR | T_IND), token->type) ||
		token->type == separator) && (op && argc < op->argc))
		{
			if (token->type != separator &&
			!overlap(op->argv[argc++], token->type))
				handle_invalid_argument(INVALID_TYPE, instr, row_nbr, token);
			token = token->next;
		}
		if ((op && argc != op->argc) || (token && token->type != endline))
			handle_invalid_argument(INVALID_COUNT, instr, row_nbr, token);
	}
}
