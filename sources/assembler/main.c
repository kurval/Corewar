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
** (3.2 Print op to check its validity)
** 4. Parse file
** 5. Try to close the .s file
** 6. Return file info in assembler struct
*/

/*
#include <stdio.h>

void			print_op(t_op *op)
{
	int	i;

	printf("op\n");
	while (op)
	{
		printf("\n");
		printf("instr_name: %s\n", op->instr_name);
		printf("argc: %d\n", op->argc);
		printf("argv: ");
		i = 0;
		while (i < op->argc)
		{
			if (i)
				printf(", ");
			printf("%d", op->argv[i++]);
		}
		printf("\n");
		printf("instr_code: %d\n", op->instr_code);
		op = op->next;
	}
}
*/

static t_asm	handle_file(char *filename)
{
	int		fd;
	char	*msg;
	t_asm	assembler;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		msg = merge_strs("Can't read source file %s", filename);
		handle_error(msg);
		ft_strdel(&msg);
	}
	assembler.op = get_op();
	//print_op(assembler.op);
	parse_file(fd, &assembler);
	if (close(fd) == -1)
	{
		msg = merge_strs("Can't close source file %s", filename);
		handle_error(msg);
		ft_strdel(&msg);
	}
	return (assembler);
}

/*
** Main
** 1. Check the params
** 2. Save info in file given as argument in assembler struct
** (3. Temporary automatic leaks test with system function)
*/

int				main(int ac, char **av)
{
	t_asm		assembler;

	check_params(ac, av);
	assembler = handle_file(av[1]);
	make_cor_file(av[1], assembler);
	system("leaks asm");
	return (0);
}
