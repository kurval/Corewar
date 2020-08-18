/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:26:39 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/22 11:07:01 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int test1(t_vm *vm)
{
    t_process *current;

    current = vm->proc_list;
    while(current)
    {
        ft_printf("ID: %d\n", current->id);
        ft_printf("POS: %d\n", current->pc);
        ft_printf("REG[0]: %d\n", current->reg[0]);
        ft_printf("\n");
        current = current->next;
    }
    return (1);
}

void test(t_vm *vm)
{
	t_process *new;
	new = (t_process*)malloc(sizeof(t_process));
	new->opcode = 11;
	new->pc = 0;
    new->next = NULL;
	// ft_printf("Valid? %d\n", get_args(vm, new));
	// ft_printf("ARG1 %d\n", new->values[0]);
	// ft_printf("ARG2 %d\n", new->values[1]);
	// ft_printf("ARG3 %d\n", new->values[2]);
    run_cycles(vm, new);
}
