/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:54 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/14 15:01:15 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Value from the Argument1 is written to the memory, to the address:
** current_position + ((Argument2 + Argument3) % IDX_MOD)
*/

void	op_sti(t_vm *vm, t_process *proc)
{
	int				value1;
	int				addr_val1;
	int				addr_val2;

	value1 = get_op_values(vm, proc, 1);
	addr_val1 = get_op_values(vm, proc, 2);
	addr_val2 = get_op_values(vm, proc, 3);
	load_into_memory(vm, proc->pc + ((addr_val1 + addr_val2) % IDX_MOD),\
	(void *)&value1, proc);
	if (vm->v_flag)
		(vm->visu->debug) ?\
		log_operation(vm, proc, W_B) : 0;
}
