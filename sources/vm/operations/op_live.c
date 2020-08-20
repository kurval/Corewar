/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:38 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:18:44 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** 1. Updates when cursor last reported alive.
** 2. If cursor's r1 == Argument1, set player as last reported alive.
*/

void	op_live(t_vm *vm, t_process *proc)
{
	if (proc == NULL)
		return ; //What should it do?
	//ft_printf("function live !%d\n", vm->lives);
	//Updates when cursor last reported alive.
	proc->last_live = vm->current_cycle;
	//If cursor's r1 == Argument1, set player as last reported alive.
	if (proc->reg[0] == get_op_values(vm, proc, proc->args[0], proc->values[0]))
		vm->last_live_id = proc->id;
	ft_printf("A process shows that player %d (%s) is alive\n", proc->id,
	proc->p_name);
}
