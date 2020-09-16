/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:42 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/16 11:08:26 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** ldi without % IDX_MOD (for the part (current_position + Argument1 +
** Argument2), for argument value if argument is T_IND, % IDX_MOD is still
** performed.
** If value written to the third argument is !0, carry is set to 0; if value
** written to the third argument is 0, carry is set to 1.
*/

void	op_lldi(t_vm *vm, t_process *proc)
{
	int				res;

	if (proc->args[0] == T_IND)
		res = int_arg(vm, proc->pc +
		(proc->values[0] % IDX_MOD));
	else
	{
		res = int_arg(vm, proc->pc +
		(get_op_values(vm, proc, 1) +
		get_op_values(vm, proc, 2)));
	}
	proc->reg[proc->values[2] - 1] = res;
	proc->carry = (!res ? 1 : 0);
	if (vm->v_flag)
		(vm->visu->debug) ?\
		log_operation(vm, proc) : 0;
}
