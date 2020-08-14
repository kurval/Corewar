/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:42 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:05:38 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_lldi(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function lldi !%d\n", vm->lives);
}