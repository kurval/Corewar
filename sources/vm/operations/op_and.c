/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:12 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:04:34 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_and(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function and !%d\n", vm->lives);
}