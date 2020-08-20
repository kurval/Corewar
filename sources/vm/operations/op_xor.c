/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:46:05 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/20 10:24:20 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Apply bit operation ^
** between ARG1 value and ARG1 value
** and save result to reg[ARG3]
** if result == 0 set carry to 1 else 0
*/

void    op_xor(t_vm *vm, t_process *proc)
{
    int res;
    int value1;
    int value2;

    value1 = get_op_values(vm, proc, proc->args[0], proc->values[0]);
    value2 = get_op_values(vm, proc, proc->args[1], proc->values[1]);
    res = value1 ^ value2;
    proc->reg[proc->values[2] - 1] = res;
    proc->carry = (res == 0) ? 1 : 0;
}