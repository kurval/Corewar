/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:02:03 by jmetelin          #+#    #+#             */
/*   Updated: 2020/07/29 17:02:07 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Handle_error
** 1. Print error msg followed by a \n to stderr
** 2. Exit with EXIT_FAILURE
*/

void		handle_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/*
** Check_args
** 1. Check that there are two arguments (e.g. "./asm champ.s")
** 2. Check that the file has the extension .s
*/

void		check_args(int argc, char **argv)
{
	char	*msg;
	int		len;
	int		i;

	if (argc != 2)
		handle_error("Usage: ./asm <sourcefile.s>");
	len = ft_strlen(argv[1]);
	i = find_last_char(argv[1], len - 1, "/");
	if ((i = find_first_char(argv[1], i + 1, ".")) == -1 || i != len - 2 ||
	argv[1][i + 1] != 's')
	{
		msg = add_str_to_str("Source file %s doesn't have the extension .s",
		argv[1]);
		handle_error(msg);
	}
}
