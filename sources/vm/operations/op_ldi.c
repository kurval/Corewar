/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:28 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:05:03 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_ldi(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function ldi !%d\n", vm->lives);
}