/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/31 10:22:40 by bkonjuha         ###   ########.fr       */
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
		vm.nb_players = validate_chapions(av);
		parse_input(ac, av, &vm);
		load_champions(&vm);
		init_processes(&vm);
		// start_visualizer(&vm);
		run_cycles(&vm);
		decleare_winner(&vm);
		free_all(&vm);
	}
	else
		ft_putstr("Usage:\n./corewar [-dump] [[-n N] file.cor]\n");
	return (0);
}
