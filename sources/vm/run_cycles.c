/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cycles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 11:31:36 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/06 13:24:45 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
 ** During the check dead cursors are removed from the list.
 ** Cursor is considered dead, if it performed operation
 ** live more than cycles_to_die or more cycles ago.
 ** Also, if cycles_to_die <= 0 all carriages are considered dead.
*/

/*
static void check_dead_processes(t_vm *vm)
{
    while(processes)
    {
        if (vm->last_live <= vm->current_cycle - vm->ctd ||\
        vm->ctd <= 0)
        {
            //kill_process
        }
    }
}
*/

/*
 ** If during last cycles_to_die cycles operation live was performed
 ** NBR_LIVE times or more, cycles_to_die is decreased with CYCLE_DELTA.
 ** If after MAX_CHECKS checks cycles_to_die was not changed, it gets decreased.
 ** Also reset period counter and lives performed in current period.
*/

static void perform_check(t_vm *vm)
{
    // check_dead_processes
    if (vm->lives >= NBR_LIVE || vm->checks >= MAX_CHECKS)
	{
        vm->ctd -= CYCLE_DELTA;
		vm->checks = 1;
    }
    else
        vm->checks++;
    vm->cycles = 0;
	vm->lives = 0;
}

/*
 ** This is the battle function which continues as long as
 ** there are processes left.
*/

void    run_cycles(t_vm *vm)
{
    // this while loop continues as long as there's processes left in a list.
    // !! We don't have proclist yet. So we'll use cycle_to_die instead 
    while(vm->ctd > 0)
    {
        vm->current_cycle++;
        vm->cycles++;
        // The check is performed once in cycles_to_die cycles if cycles_to_die > 0.
        // After it's value becomes less than 1, the check is performed each cycle.
        if (vm->ctd <= 0 || vm->cycles == vm->ctd)
            perform_check(vm);
    }
}