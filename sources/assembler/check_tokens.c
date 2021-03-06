/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:52:34 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/05 16:52:38 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Check_token_validity
** 1. Checks that the instruction is valid and has a valid amount of valid
**    arguments
** 2. Prints the correct error msg to STDERR
*/

static void		check_instr_validity(t_token *token, t_op **op)
{
	while (*op && !ft_strequ((*op)->instr_name, token->content))
		*op = (*op)->next;
	if (!(*op))
		handle_error_msg(INVALID_INSTR, token);
}

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

/*
** Check_token_order
** 1. Checks that the tokens are in a valid order:
**    (cmd_str string |
**    (label) (instruction T_REG|T_DIR|T_IND
**    (separator T_REG|T_DIR|T_IND (separator T_REG|T_DIR|T_IND)))
**    endline
** 2. Prints the correct error msg to STDERR
*/

static int		is_arg_or_sep(int ord, int type)
{
	if ((!(ord % 2) && overlap((T_REG | T_DIR | T_IND), type)) ||
	(ord % 2 && type == separator))
		return (1);
	return (0);
}

static t_token	*check_instr_token_order(t_token *token)
{
	int i;

	if (token && token->type == label)
		token = token->next;
	if (token && token->type == instruction)
	{
		token = token->next;
		i = 0;
		while (token && is_arg_or_sep(i, token->type))
		{
			i++;
			token = token->next;
		}
		if (!(i % 2) && token)
			handle_error_msg(SYNTAX_ERROR, token);
	}
	return (token);
}

void			check_token_order(t_token *token)
{
	if (token && overlap(token->type, cmd_str))
	{
		token = token->next;
		if (!token || token->type != string)
			handle_error_msg(SYNTAX_ERROR, token);
		else
			token = token->next;
	}
	else
		token = check_instr_token_order(token);
	if (!token || token->type != endline)
		handle_error_msg(SYNTAX_ERROR, token);
}
