/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/12 18:30:27 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
#include "../../libft/libft.h"

int	main(int ac, char **av)
{
	t_vm	vm;
	t_arena	arena;
	t_op	op[16];
	
	if (ac >= 2)
	{
		init_vm(&vm);
		init_arena(&vm, &arena);
		get_op(op);
		validate_chapions(av);
		parse_input(av, &vm);
		run_cycles(&vm);
		ft_printf("\nCurrent cycle %d\n", vm.current_cycle);
		//print_arena(&arena);
	}
	return (0);
}
