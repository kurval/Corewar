/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/25 17:12:12 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	main(int ac, char **av)
{
	t_vm	vm;
	t_arena	arena;

	if (ac >= 2)
	{
		init_vm(&vm);
		init_arena(&vm, &arena);
		get_op(vm.operations);
		validate_chapions(av);
		parse_input(ac, av, &vm);
		load_champions(&vm);
		init_processes(&vm);
		run_cycles(&vm);
		decleare_winner(&vm);
		free_all(&vm);
	}
	else
	{
		ft_putstr("Usage:\n./corewar [--dump] [-n N] ");
		ft_putendl("file.cor");
	}
	return (0);
}
