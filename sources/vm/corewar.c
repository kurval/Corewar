/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/11 01:06:56 by bkonjuha         ###   ########.fr       */
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
		vm.nb_players = validate_chapions(av);
		parse_input(av, &vm);
		load_champions(&vm);
		init_processes(&vm);
		if (vm.v_flag)
			start_visualizer(&vm);
		run_cycles(&vm);
		decleare_winner(&vm);
	}
	else
		ft_putstr("Usage:\n./corewar [-dump] [-a] [-v] [[-n N] file.cor]\n");
	return (0);
}
