/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:42 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/09 21:19:56 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** ld without % IDX_MOD.
** Original corewar works wrong: if argument type is T_IND it reads 2 bytes into
** T_REG instead of 4.
*/

void	op_lld(t_vm *vm, t_process *proc)
{
	int	res;

	if (proc->args[0] == T_IND)
		res = int_arg(vm, proc->pc +
		proc->values[0]);
	else
		res = get_op_values(vm, proc, 1);
	proc->reg[proc->values[1] - 1] = res;
	proc->carry = (!res ? 1 : 0);
}
