/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/12 16:42:16 by vkurkela         ###   ########.fr       */
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
		parse_input(ac, av, &vm);
		load_champions(&vm);
		init_processes(&vm);
		if (vm.v_flag)
			start_visualizer(&vm);
		run_cycles(&vm);
		decleare_winner(&vm);
	}
	else
	{
		ft_putstr_fd("Usage:\n./corewar ", 2);
		ft_putstr_fd("[-dump N | -d N] [-a] [-l] [-v] [[-n N] file.cor]\n", 2);
	}
	return (0);
}
