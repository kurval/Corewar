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
** 2. Prints the correct error msg to STDERR
*/

/*
** #include <stdio.h>
**
** static void	print_token(t_token *token)
** {
** 	printf("token\n");
** 	printf("type %d\n", token->type);
** 	printf("content %s\n", token->content);
** 	printf("cursor row %d col %d\n\n", token->cursor->row, token->cursor->col);
** }
*/

char	*pad_nbr(int nbr, int size)
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

void	handle_syntax_error(t_token *token)
{
	char	*syntax_error;
	char	**strs;

	if (!(strs = (char **)malloc(sizeof(char *) * 5)))
		handle_error(MALLOC_ERROR);
	strs[0] = pad_nbr(token->cursor->row, 3);
	strs[1] = pad_nbr(token->cursor->col, 3);
	if (!(strs[2] = ft_strdup(token_type_str(token->type))) ||
	!(strs[3] = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	strs[4] = NULL;
	if (token->type != ENDLINE)
	{
		syntax_error = add_strs_to_str(
		"Syntax error at token [TOKEN] [%s:%s] %s \"%s\"", strs);
	}
	else
	{
		syntax_error = add_strs_to_str(
		"Syntax error at token [TOKEN] [%s:%s] %s", strs);
	}
	del_array(strs);
	handle_error(syntax_error);
}

void	check_token_order(t_token *token)
{
	int	i;

	if (token->type == CMD_STR)
	{
		token = token->next;
		if (!token || token->type != STRING)
			handle_syntax_error(token);
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
			while (token && ((!(i % 2) && overlap((T_REG | T_DIR | T_IND),
			token->type)) || (i % 2 && token->type == SEPARATOR)) && i++ < 5)
				token = token->next;
			if (!(i % 2))
				handle_syntax_error(token);
		}
	}
	if (!token || token->type != ENDLINE)
		handle_syntax_error(token);
}
