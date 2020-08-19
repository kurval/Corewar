/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:26:39 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/19 21:37:30 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int test2(int i)
{
    return (i);
}

static int test1(t_vm *vm)
{
    t_process *new;
	new = (t_process*)malloc(sizeof(t_process));
	new->opcode = 11;
	new->pc = 0;
    new->carry = 1;
    new->next = NULL;
    new->reg[1] = 10;
    new->reg[2] = 6;
    new->reg[1] = 10;
	// ft_printf("Valid? %d\n", get_args(vm, new));
	// ft_printf("ARG1 %d\n", new->values[0]);
	// ft_printf("ARG2 %d\n", new->values[1]);
	// ft_printf("ARG3 %d\n", new->values[2]);
    run_cycles(vm, new);
    ft_printf("\nCurrent cycle %d\n", vm->current_cycle);
    return (1);
}

void test(t_vm *vm)
{
    /*
        Write your tests in this file as a static function
        which return 1 if test is OK and 0 if test FAILS
    */

    int testnum = 2; // NUmber of tests : raise this number if you add more tests
    int i = 0;
    int tests[testnum];

    // add test row here for invoke your function
    tests[i++] = test1(vm);
    tests[i++] = test2(1);
    
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
