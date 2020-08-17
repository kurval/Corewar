/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/17 22:55:48 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
static void test(t_vm *vm)
{
	t_process *new;
	new = (t_process*)malloc(sizeof(t_process));
	new->next = NULL;
	new->opcode = 2;
	new->current_position = 12;
	get_args(vm, new);
	ft_printf("ARG1 %d\n", new->values[0]);
	ft_printf("ARG2 %d\n", new->values[1]);
	ft_printf("ARG3 %d\n", new->values[2]);
}
*/

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
		ft_printf("\nCurrent cycle %d\n", vm.current_cycle);
		// test(&vm);
		// print_arena(&arena);
		free_all(&vm);
	}
	return (0);
}
