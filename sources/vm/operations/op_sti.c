/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:54 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:06:02 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_sti(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function sti !%d\n", vm->lives);
}