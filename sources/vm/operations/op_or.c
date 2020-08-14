/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:46 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:05:45 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_or(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function or !%d\n", vm->lives);
}