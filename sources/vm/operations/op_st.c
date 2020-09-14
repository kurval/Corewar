/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:51 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/14 15:01:15 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** If Argument2 is of type T_REG,
** >set value from registry <Argument1> into registry <Argument2>
** If Argument2 is of type T_IND,
** >set value from registry <Argument1> into memory.
** Address is calculated as follows: (current_position + (Argument2 % IDX_MOD))
*/

void	op_st(t_vm *vm, t_process *proc)
{
	int				value1;

	value1 = get_op_values(vm, proc, 1);
	if (proc->args[1] == T_REG)
		proc->reg[proc->values[1] - 1] = value1;
	else if (proc->args[1] == T_IND)
		load_into_memory(vm, proc->pc + (proc->values[1] % IDX_MOD),\
		(void *)&value1, proc);
	if (vm->v_flag)
		(vm->visu->debug) ?\
		log_operation(vm, proc, W_B) : 0;
}
