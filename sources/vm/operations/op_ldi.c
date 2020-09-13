/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:28 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/13 20:28:22 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Read 4 bytes from the address: current_position + (Argument1 + Argument2) %
** IDX_MOD, and save to the Argument3
** If Argument1 is of type T_IND, value (4 bytes) for address calculation is
** read from memory: current_position + Argument1 % IDX_MOD
*/

void	op_ldi(t_vm *vm, t_process *proc)
{
	int				res;

	if (proc->args[0] == T_IND)
		res = int_arg(vm, proc->pc +
		(proc->values[0] % IDX_MOD));
	else
	{
		res = int_arg(vm, proc->pc +
		(get_op_values(vm, proc, 1) +
		get_op_values(vm, proc, 2)) % IDX_MOD);
	}
	proc->reg[proc->values[2] - 1] = res;
	if (vm->v_flag)
		(vm->visu->debug) ?\
		log_operation(vm, proc, " proc id executed ldi\n", 0) : 0;
}
