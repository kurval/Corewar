/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:07 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:10 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Handle file
** 1. Check the params
** 2. Try to open the .s file
** 3 Create op linked list
** 4. Parse file
** 5. Try to close the .s file
** 6. Return file info in assembler struct
*/

static t_asm	handle_file(char *filename, t_asm assembler)
{
	int		fd;
	char	*msg;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		msg = add_str_to_str("Can't read source file %s", filename);
		handle_error(msg);
	}
	assembler.op = get_op();
	parse_file(fd, &assembler);
	if (close(fd) == -1)
	{
		msg = add_str_to_str("Can't close source file %s", filename);
		handle_error(msg);
	}
	return (assembler);
}

char			*get_usage(void)
{
	return ("Usage: ./asm [-hefx] <sourcefile.s>\n \
	-h	prints usage\n \
	-e	prints all errors instead of only the first one\n \
	-r	creates .cor file in current location\n \
	-x	prints hexdump");
}

/*
** Main
** 1. Check the args
** 2. Save info in file given as argument in assembler struct
** (3. Temporary automatic leaks test with system function)
*/

int				main(int argc, char **argv)
{
	t_asm		assembler;
	char		*dest;
	char		*source;

	if (!(source = check_args(argc, argv, &dest)))
		handle_error(get_usage());
	if (overlap(get_flags(), FLAG_H))
	{
		ft_printf(get_usage());
		exit(0);
	}
	assembler = handle_file(source, assembler);
	make_cor_file(source, assembler);
	free_memory(assembler.op, &assembler.champ);
	return (0);
}
