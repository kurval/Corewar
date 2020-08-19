/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:46:09 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/19 16:57:19 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_zjmp(t_vm *vm, t_process *proc)
{
    if (proc->carry == 1)
        proc->jump = (proc->values[0] % IDX_MOD);
    if (vm)
        return ;
}