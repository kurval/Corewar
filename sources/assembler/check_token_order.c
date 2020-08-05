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
** Check_token_order
** 1. Checks that the tokens are in a valid order:
**    (CMD_STR STRING |
**    (LABEL) (INSTRUCTION T_REG|T_DIR|T_IND
**    (SEPARATOR T_REG|T_DIR|T_IND (SEPARATOR T_REG|T_DIR|T_IND)))
**    ENDLINE
** 2. Prints the correct error msg to STDERR (TO DO)
*/

/*
#include <stdio.h>

static void	print_token(t_token *token)
{
	printf("token\n");
	printf("type %d\n", token->type);
	printf("content %s\n", token->content);
	printf("cursor row %d col %d\n\n", token->cursor->row, token->cursor->col);
}
*/

void	check_token_order(t_token *token, t_op *op)
{
	int	i;

	if (token->type == CMD_STR)
	{
		token = token->next;
		if (!token || token->type != STRING)
			handle_error("Error");
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
			while (token &&
			((!IS_ODD(i) && overlap((T_REG | T_DIR | T_IND), token->type)) ||
			(IS_ODD(i) && token->type == SEPARATOR)) && i++ < 5)
				token = token->next;
			if (IS_ODD(i) && token->type != ENDLINE)
				handle_error("Error");
		}
	}
	if (!token || token->type != ENDLINE)
		handle_error("Error");
}
