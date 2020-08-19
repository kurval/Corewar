/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:59 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/19 21:41:48 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** subtraction reg[ARG1] - reg[ARG2] and
** adding result to reg[ARG3]
** ** if result == 0 set carry to 1 else 0 
*/

void    op_sub(t_vm *vm, t_process *proc)
{
    int sub;

    sub = proc->reg[proc->values[0] - 1] - proc->reg[proc->values[1] - 1];
    proc->reg[proc->values[2] - 1] = sub;
    proc->carry = (sub == 0) ? 1 : 0;
    if (vm)
        return ;
}