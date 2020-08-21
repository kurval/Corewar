/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/21 13:24:46 by vkurkela         ###   ########.fr       */
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
		init_processes(&vm);
		test(&vm); // for testing
		free_all(&vm);
	}
	return (0);
}
