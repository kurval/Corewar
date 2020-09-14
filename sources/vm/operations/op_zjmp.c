/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:46:09 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/14 15:01:15 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** if carry == 1 move cursor to:
** current_position + (T_DIR % IDX_MOD)
*/

void	op_zjmp(t_vm *vm, t_process *proc)
{
	if (proc->carry == 1)
		proc->jump = (proc->values[0] % IDX_MOD);
	if (vm->v_flag)
		(vm->visu->debug) ?\
		log_operation(vm, proc, W_B) : 0;
}
