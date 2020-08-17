/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_opfunctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:42:25 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:35:05 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void    *assign_opfunctions(int opcode)
{
    void    (*f)(t_vm *vm, t_process *proc);

    opcode == 1 ? f = op_live : 0;
    opcode == 2 ? f = op_ld : 0;
    opcode == 3 ? f = op_st : 0;
    opcode == 4 ? f = op_add : 0;
    opcode == 5 ? f = op_sub : 0;
    opcode == 6 ? f = op_and : 0;
    opcode == 7 ? f = op_or : 0;
    opcode == 8 ? f = op_xor : 0;
    opcode == 9 ? f = op_zjmp : 0;
    opcode == 10 ? f = op_ldi : 0;
    opcode == 11 ? f = op_sti : 0;
    opcode == 12 ? f = op_fork : 0;
    opcode == 13 ? f = op_lld : 0;
    opcode == 14 ? f = op_lldi : 0;
    opcode == 15 ? f = op_lfork : 0;
    opcode == 16 ? f = op_aff : 0;
    
    return (f); 
}