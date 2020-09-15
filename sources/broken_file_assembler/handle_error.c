/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:52:34 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/05 16:52:38 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Handle_error
** 1. Print error msg followed by a \n to stderr
** 2. Exit with EXIT_FAILURE
*/

void	handle_error(char *msg)
{
	static int exit_status = 0;

	if (msg)
	{
		exit_status = 1;
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (!(overlap(g_flags, flag_error_debug)) ||
	(msg == EXIT_IF_ERRORS && exit_status) || ft_strequ(msg, MALLOC_ERROR))
	{
		if (overlap(g_flags, flag_l))
			system("leaks asm");
		exit(EXIT_FAILURE);
	}
}

void	handle_error_free_msg(char *msg)
{
	handle_error(msg);
	ft_strdel(&msg);
}

char	*token_type_str(t_type type)
{
	if (type == reg)
		return ("REGISTER");
	if (type == direct)
		return ("DIRECT");
	if (type == indirect)
		return ("INDIRECT");
	if (type == instruction)
		return ("INSTRUCTION");
	if (type == label)
		return ("LABEL");
	if (type == separator)
		return ("SEPARATOR");
	if (type == string)
		return ("STRING");
	if (overlap(type, cmd_str))
		return (type == command_name ? "COMMAND_NAME" : "COMMAND_COMMENT");
	if (type == direct_label)
		return ("DIRECT_LABEL");
	if (type == indirect_label)
		return ("INDIRECT_LABEL");
	if (type == indirect)
		return ("INDIRECT");
	if (type == endline)
		return ("ENDLINE");
	return (NULL);
}

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
