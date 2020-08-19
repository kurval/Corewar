/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:44:03 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/20 00:18:04 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** addition reg[ARG1] + reg[ARG2] and
** adding result to reg[ARG3]
** if result == 0 set carry to 1 else 0 
*/

void    op_add(t_vm *vm, t_process *proc)
{
    int sum;
    int value1;
    int value2;

    value1 = get_op_values(vm, proc, proc->args[0], proc->values[0]);
    value2 = get_op_values(vm, proc, proc->args[1], proc->values[1]);

    sum = value1 + value2;
    proc->reg[proc->values[2] - 1] = sum;
    proc->carry = (sum == 0) ? 1 : 0;
    if (vm)
        return ;
}