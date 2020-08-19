/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:44:03 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/19 21:43:42 by vkurkela         ###   ########.fr       */
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

    sum = proc->reg[proc->values[0] - 1] + proc->reg[proc->values[1] - 1];
    proc->reg[proc->values[2] - 1] = sum;
    proc->carry = (sum == 0) ? 1 : 0;
    if (vm)
        return ;
}