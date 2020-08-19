/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/22 16:52:46 by bkonjuha         ###   ########.fr       */
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
		test(&vm); // for testing
		run_cycles(&vm);
		ft_printf("\nCurrent cycle %d\n", vm.current_cycle);
		//print_arena(&arena);

		t_process *new;
		if (!(new = (t_process*)malloc(sizeof(t_process))))
			exit(1);
		new->next = NULL;
		free_all(&vm);
	}
	return (0);
}
