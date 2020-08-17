/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:18 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:04:47 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_fork(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function fork !%d\n", vm->lives);
}