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

static t_asm	handle_file(char *filename)
{
	t_asm	assembler;
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

/*
** Main
** 1. Check the args
** 2. Save info in file given as argument in assembler struct
** (3. Temporary automatic leaks test with system function)
*/

int				main(int argc, char **argv)
{
	t_asm		assembler;

	check_args(argc, argv);
	assembler = handle_file(argv[1]);
	make_cor_file(argv[1], assembler);
	free_memory(assembler.op, &assembler.champ);
	return (0);
}