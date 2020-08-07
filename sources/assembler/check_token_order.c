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

char		*pad_nbr(int nbr, int size)
{
	char	*padded_nbr;
	char	*s1;
	char	*s2;
	int		len;

	if (!(s2 = ft_itoa(nbr)))
		handle_error(MALLOC_ERROR);
	if (size - (len = ft_strlen(s2)) > 0)
	{
		if (!(s1 = ft_strnew(size - len)))
			handle_error(MALLOC_ERROR);
		ft_memset((void *)s1, '0', size - len);
		padded_nbr = join_free_strs(s1, s2);
	}
	else
		padded_nbr = s2;
	return (padded_nbr);
}

void		handle_error_msg(int error, t_token *token)
{
	char	*msg;
	char	**strs;

	if (!(strs = (char **)malloc(sizeof(char *) * 6)) ||
	!(strs[0] = ft_strdup((overlap(SYNTAX_ERROR, error) ? "Syntax error" :
	"Invalid instruction"))))
		handle_error(MALLOC_ERROR);
	strs[1] = pad_nbr(token->cursor->row, 3);
	strs[2] = pad_nbr(token->cursor->col, 3);
	if (!(strs[3] = ft_strdup(token_type_str(token->type))) ||
	!(strs[4] = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	strs[5] = NULL;
	if (token->type != ENDLINE)
		msg = add_strs_to_str("%s at token [TOKEN] [%s:%s] %s \"%s\"", strs);
	else
		msg = add_strs_to_str("%s at token [TOKEN] [%s:%s] %s", strs);
	del_array(strs);
	handle_error(msg);
}

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

	if (token->type == CMD_STR)
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
