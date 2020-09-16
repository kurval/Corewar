/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:23 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/16 19:17:26 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Load value from Argument1 into registry number Argument2.
** If Argument1 type is T_IND, value to be loaded is read from memory. Address
** is calculated as follows: current_position + Argument1 % IDX_MOD
** If result is 0, set carry to 1. If result is !0, set carry to 0.
*/

void	op_ld(t_vm *vm, t_process *proc)
{
	int	res;

	res = get_op_values(vm, proc, 1);
	proc->reg[proc->values[1] - 1] = res;
	proc->carry = (!res ? 1 : 0);
	if (vm->v_flag)
		(vm->visu->debug) ?\
		log_operation(vm, proc) : 0;
}
