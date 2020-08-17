/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:23 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:04:57 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_ld(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function ld !%d\n", vm->lives);
}