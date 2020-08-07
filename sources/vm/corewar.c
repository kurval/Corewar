/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:30:41 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/07 14:46:08 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
#include "../../libft/libft.h"

int	main(int ac, char **av)
{
	t_vm vm;

	if (ac >= 2)
	{
		init_vm(&vm);
		validate_chapions(av);
		parse_input(av, &vm);
		run_cycles(&vm);
		ft_printf("\nCurren cycle %d\n", vm.current_cycle);
	}
	return (0);
}
