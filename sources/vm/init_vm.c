/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:33:54 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/07 14:37:16 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	init_vm(t_vm *vm)
{
	vm->checks = 0;
	vm->current_cycle = 0;
	vm->cycles = 0;
	vm->last_live_id = 0;
	vm->ctd = CYCLE_TO_DIE;
	vm->lives = 0;
	vm->dump_cycle = 0;
}
