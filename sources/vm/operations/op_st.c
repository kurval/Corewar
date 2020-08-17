/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:51 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:05:55 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void    op_st(t_vm *vm, t_process *proc)
{
    if (proc == NULL)
        ;
    ft_printf("function st !%d\n", vm->lives);
}