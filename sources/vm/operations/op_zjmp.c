/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:46:09 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/20 14:19:30 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** if carry == 1 move cursor to:
** current_position + (T_DIR % IDX_MOD)							
*/

void    op_zjmp(t_vm *vm, t_process *proc)
{
    if (proc->carry == 1)
        proc->jump = (proc->values[0] % IDX_MOD);
    if (vm)
        return ;
}