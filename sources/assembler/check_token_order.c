/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_order.c                                :+:      :+:    :+:   */
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

void		check_token_validity(t_token *token, t_op *op)
{
	int	argc;

	if (token->type == LABEL)
		token = token->next;
	if (token && token->type == INSTRUCTION)
	{
		while (op && !ft_strequ(op->instr_name, token->content))
			op = op->next;
		if (!op)
			handle_error_msg(INVALID_INSTR, token);
		token = token->next;
		argc = 0;
		while (token && (overlap((T_REG | T_DIR | T_IND), token->type) ||
		token->type == SEPARATOR) && argc < op->argc)
		{
			if (token->type != SEPARATOR &&
			!overlap(op->argv[argc++], token->type))
				handle_error("Invalid argument");
			token = token->next;
		}
		if (argc != op->argc || token->type != ENDLINE)
			handle_error("Invalid amount of arguments");
	}
}

/*
**	Checks that champion info is not set multiple times,
**	and that info is set before other types of tokens.
*/

void		check_statement_order(t_token *token, t_champ *champ)
{
	if (token->type != ENDLINE)
	{
		if (overlap(token->type, CMD_STR))
		{
			if (token->type == COMMAND_NAME && champ->name)
				handle_error_msg(SYNTAX_ERROR, token);
			if (token->type == COMMAND_COMMENT && champ->comment)
				handle_error_msg(SYNTAX_ERROR, token);
		}
		else if (!champ->done)
			handle_error_msg(SYNTAX_ERROR, token);
	}
}

/*
** Check_token_order
** 1. Checks that the tokens are in a valid order:
**    (CMD_STR STRING |
**    (LABEL) (INSTRUCTION T_REG|T_DIR|T_IND
**    (SEPARATOR T_REG|T_DIR|T_IND (SEPARATOR T_REG|T_DIR|T_IND)))
**    ENDLINE
** 2. Prints the correct error msg to STDERR
*/

static int	is_arg_or_sep(int ord, int type)
{
	if ((!(ord % 2) && overlap((T_REG | T_DIR | T_IND), type)) ||
	(ord % 2 && type == SEPARATOR))
		return (1);
	return (0);
}

void		check_token_order(t_token *token)
{
	int	i;

	if (overlap(token->type, CMD_STR))
	{
		token = token->next;
		if (!token || token->type != STRING)
			handle_error_msg(SYNTAX_ERROR, token);
		token = token->next;
	}
	else
	{
		if (token->type == LABEL)
			token = token->next;
		if (token && token->type == INSTRUCTION)
		{
			token = token->next;
			i = 0;
			while (token && is_arg_or_sep(i, token->type) && i++ < 5)
				token = token->next;
			if (!(i % 2))
				handle_error_msg(SYNTAX_ERROR, token);
		}
	}
	if (!token || token->type != ENDLINE)
		handle_error_msg(SYNTAX_ERROR, token);
}
