/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:44:03 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:04:13 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_add(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function add !%d\n", vm->lives);
}