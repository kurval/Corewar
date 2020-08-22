/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:18 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/22 13:48:31 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Creates an identical copy of the process (cursor) and
** places it to the position (Argument1 % IDX_MOD) + position of parent cursor					
*/

void    op_fork(t_vm *vm, t_process *proc)
{
    int             value1;
    t_process       *new;

    value1 = proc->values[0];
    new = copy_proc(vm, proc);
    new->pc = get_addr(proc->pc + (value1 % IDX_MOD));
    add_to_list(new, &vm->proc_list);
}