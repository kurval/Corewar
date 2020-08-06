/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/06 11:41:06 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
#include "../../libft/libft.h"

int	main(int ac, char **av)
{
	t_vm *vm;

	if (ac >= 2)
	{
		vm = init_vm();
		validate_chapions(av);
		parse_input(av, vm);
		run_cycles(vm);
		ft_printf("\n ending %p\n", vm->checks);
	}
	return (0);
}
