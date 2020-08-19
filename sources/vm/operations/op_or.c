/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:46 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/19 22:14:47 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Apply bit operation |
** between ARG1 value and ARG1 value
** and save result to reg[ARG3]
** if result == 0 set carry to 1 else 0 
*/

void    op_or(t_vm *vm, t_process *proc)
{
    int res;

    res = proc->values[0] | proc->values[1];
    proc->reg[proc->values[2] - 1] = res;
    proc->carry = (res == 0) ? 1 : 0;
    if (vm)
        return ;
}