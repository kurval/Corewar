/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:26:39 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/21 15:35:15 by vkurkela         ###   ########.fr       */
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
    /*
        Write your tests in this file as a static function
        which return 1 if test is OK and 0 if test FAILS
    */

    int testnum = 1; // NUmber of tests : raise this number if you add more tests
    int i = 0;
    int tests[testnum];

    // add test row here for invoke your function
    tests[i++] = test1(vm);
    
    i = 0;
    while (i < testnum)
    {
        if (tests[i])
            ft_printf(GREEN "Test %d OK\n" RESET, i);
        else
            ft_printf(RED "FAIL %d OK\n" RESET, i);
        i++;
    }
}
