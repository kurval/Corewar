/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:59 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:06:10 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_sub(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function sub !%d\n", vm->lives);
}