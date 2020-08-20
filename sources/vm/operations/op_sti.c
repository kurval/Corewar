/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:54 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/20 23:43:48 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Value from the Argument1 is written to the memory, to the address:
** current_position + ((Argument2 + Argument3) % IDX_MOD)
*/

void    op_sti(t_vm *vm, t_process *proc)
{
    int value1;
    int addr_val1;
    int addr_val2;
    unsigned int addr;

    value1 = get_op_values(vm, proc, 1);
    addr_val1 = get_op_values(vm, proc, 2);
    addr_val2 = get_op_values(vm, proc, 3);
    addr = proc->pc + ((addr_val1 + addr_val2) % IDX_MOD);
    load_into_memory(vm, addr, (void *)&value1);
}