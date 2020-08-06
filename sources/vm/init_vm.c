/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:33:54 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/06 13:04:08 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

t_vm	*init_vm(void)
{
	t_vm *vm;

	if (!(vm = (t_vm *)malloc(sizeof(t_vm))))
		ft_errno(VM_ERROR);
	vm->checks = 0;
	vm->current_cycle = 0;
	vm->cycles = 0;
	vm->last_live_id = 0;
	vm->ctd = CYCLE_TO_DIE;
	vm->lives = 0;
	return (vm);
}
