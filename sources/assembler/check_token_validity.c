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