/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:07 by atuomine          #+#    #+#             */
/*   Updated: 2020/09/11 01:07:26 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** A simple function to check if the given types overlap.
** Returns the sum of values that overlap.
**
** Examples of usage:
** Can be used to check if currently checked argument type is valid:
** overlap(T_REG, token->type);
** overlap(T_REG | T_IND, token->type);
**
** overlap(T_REG | T_IND | T_DIR, T_IND | T_DIR); // returns (T_IND | T_DIR)
*/

int				overlap(int type1, int type2)
{
	return (type1 & type2);
}

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
	if (overlap(g_flags, flag_e))
		toggle_error_debug_flag();
	assembler.op = get_op();
	parse_file(fd, &assembler);
	if (overlap(g_flags, flag_e))
	{
		handle_error(EXIT_IF_ERRORS);
		toggle_error_debug_flag();
	}
	if (close(fd) == -1)
	{
		msg = add_str_to_str("Can't close source file %s", filename);
		handle_error(msg);
	}
	return (assembler);
}

char			*get_usage(void)
{
	return ("Usage:\n \
	./asm [-h] [-e] [-d DIR] [-x] [-f FILE] [-l] <sourcefile.s>\n \
	or:\n \
	./asm -z <sourcefile.cor>\n \
	-h      prints the usage\n \
	-e      prints all the errors instead of only the first one\n \
	-d DIR  creates the .cor file to the directory DIR\n \
	-x      prints the hexdump\n \
	-f FILE names the .cor file FILE\n \
	-l      prints memory leaks\n \
	-z      disassembles a .cor file to a .s file\n \
	\n \
	If a file path is defined in both the -d and -f options,\n \
	the one in the -f option is used.");
}

static void		dasm_main(int argc, char **argv)
{
	char	*deasm_file;

	if (argc != 3)
		handle_error(get_usage());
	if (!(deasm_file = validate_file(argv[2])))
		handle_error("Could not open file");
	dasm(argv[2], deasm_file);
	ft_printf("%s file created\n", deasm_file);
	exit(EXIT_SUCCESS);
}

/*
** Main
** 1. Check the args
** 2. Save info in the file given as an argument in the assembler struct
*/

int				main(int argc, char **argv)
{
	t_asm		assembler;
	char		*source;

	if (ft_strequ(argv[1], "-z") || ft_strequ(argv[1], "-Z"))
		dasm_main(argc, argv);
	else if (!(source = check_args(argc, argv)))
		handle_error(get_usage());
	if (overlap(g_flags, flag_h))
	{
		ft_putstr_fd(get_usage(), 2);
		if (overlap(g_flags, flag_l))
			system("leaks asm");
		exit(0);
	}
	assembler = handle_file(source);
	handle_d_and_f_flags(&source);
	make_cor_file(source, assembler);
	free_memory(assembler.op, &assembler.champ);
	if (overlap(g_flags, flag_l))
		system("leaks asm");
	return (0);
}
