/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c			                                :+:      :+:    :+:   */
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
	strs[2] = pad_nbr(token->cursor->col + 1, 3);
	if (!(strs[3] = ft_strdup(token_type_str(token->type))) ||
	!(strs[4] = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	strs[5] = NULL;
	if (token->type != ENDLINE)
		msg = add_strs_to_str("%s at token [TOKEN][%s:%s] %s \"%s\"", strs);
	else
		msg = add_strs_to_str("%s at token [TOKEN][%s:%s] %s", strs);
	del_array(strs);
	handle_error(msg);
}

void	lexical_error(t_cursor cursor)
{
	char	**cursor_str;
	char	*msg;

	if (!(cursor_str = (char **)malloc(sizeof(char *) * 3)))
		handle_error(MALLOC_ERROR);
	cursor_str[0] = ft_itoa(cursor.row);
	cursor_str[1] = ft_itoa(cursor.col);
	cursor_str[2] = NULL;
	msg = add_strs_to_str("Lexical error at [%s:%s]", cursor_str);
	del_array(cursor_str);
	handle_error(msg);
}
/*
** Handle_error
** 1. Print error msg followed by a \n to stderr
** 2. Exit with EXIT_FAILURE
*/

void		handle_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	system("leaks asm");
	exit(EXIT_FAILURE);
}
