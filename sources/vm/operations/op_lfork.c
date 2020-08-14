/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:33 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:05:13 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_lfork(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function lfork !%d\n", vm->lives);
}