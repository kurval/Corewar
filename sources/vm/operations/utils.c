/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 23:25:59 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/20 14:22:01 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** This function returns value depending on type:
** If type is T_REG it return value from registry number
** If type is T_IND it return value from position + T_IND
** If type is T_DIR it return number from T_DIR argument
*/

int    get_op_values(t_vm *vm, t_process *proc, int arg)
{
    int value;
    int type;

    value = proc->values[arg - 1];
    type = proc->args[arg - 1];
    if (type == T_REG)
		return (proc->reg[value - 1]);
    else if (type == T_IND)
        return (int_arg(vm, proc->pc + value % IDX_MOD));
    else if (type == T_DIR)
		return (value);
    return (0);
}