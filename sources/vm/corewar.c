/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/08/21 16:03:35 by vkurkela         ###   ########.fr       */
=======
/*   Updated: 2020/08/16 14:24:12 by bkonjuha         ###   ########.fr       */
>>>>>>> Parse Champions and allocate to arena
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
		parse_input(av, &vm);
		load_champions(&vm);
		run_cycles(&vm);
		decleare_winner(&vm);
		free_all(&vm);
	}
	return (0);
}
