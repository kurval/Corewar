/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:46:09 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:06:36 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_zjmp(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function zjmp !%d\n", vm->lives);
}