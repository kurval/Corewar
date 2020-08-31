/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:33 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/22 12:16:34 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** fork without % IDX_MOD
*/

void	op_lfork(t_vm *vm, t_process *proc)
{
	int			value1;
	t_process	*new;

	value1 = proc->values[0];
	new = copy_proc(vm, proc);
	new->pc = get_addr(proc->pc + value1);
	add_to_list(new, &vm->proc_list);
}
