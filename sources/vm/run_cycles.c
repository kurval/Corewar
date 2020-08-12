/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cycles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 11:31:36 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/12 18:28:53 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Setting a new opcode and wait_cycles after cursor
** has moved. During the very first execution cycle,
** all carriages will receive an opcode value.
** If read value is not a valid operation code,
** save value and set wait_cycles = 0 (1 because it
** gets decreased on the next statement)
*/
/*
static void set_opcode(t_vm *vm, t_process *proc)
{
    proc->opcode = vm->arena[proc->current_position];
    if (proc->opcode == 0 || proc->opcode > NB_OPERATIONS)
		proc->wait_cycles = 1;
	else
		proc->wait_cycles = vm->operations[opcode - 1];
}
*/

/*
** If wait_cycles == 0 it's time to execute the operation, that is saved in the cursor.
** - If saved operation code is a valid code and operation requires encoding byte, validate it.
** - If encoding byte is valid and there are registries among the arguments, validate registry numbers.
** - If all the checks were successfully passed, execute the operation and move cursor to the next operation.
** - If operation code is not valid, move cursor to the next byte.
** - If operation code is valid, but encoding byte is invalid or one of arguments is not valid.
** --> Cursor must be moved to the next operation without execution.
** To get to the next operation, cursor must skip operation byte, encoding byte (if present),
** and arguments saved in the encoding byte.
*/

/*
static void	execute_operation(t_vm *vm, t_process *proc)
{
    int i;

    if (!proc->wait_cycles)
		set_opcode(vm, proc);
    proc->wait_cycles -= 1;

    //Execute the operation
    if (!proc->wait_cycles)
    {
        If all the checks were successfully passed
            execute the operation STRUCT FOR OPERATION FUNCTIONS
        else
            If operation code is not valid, move cursor to the next byte.
            proc->jump = 1;

        move cursor to the next operation:
            proc->current_position = NEED FUNCTION TO MOVE CURSOR current_position + jump
    }
}
*/

/*
** During the check dead cursors are removed from the list.
** Cursor is considered dead, if it performed operation
** live more than cycles_to_die or more cycles ago.
** Also, if cycles_to_die <= 0 all carriages are considered dead.
*/

/*
static void check_dead_processes(t_vm *vm, t_process *proc)
{
    while(processes)
    {
        if (vm->last_live <= vm->current_cycle - vm->ctd ||\
        vm->ctd <= 0)
        {
            //kill_process
        }
        else
            next->process
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
    // check_dead_processes()
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
        /* In each cycle vm checks the whole list of cursors (execute_statements function)
        - Assigns a new opcode
        - Decrease wait_cycles
        - Execute the operation
        while (processes)
        {
            execute_statements(vm, proclist, operations)
            next->process
        }
        */
        // The check is performed once in cycles_to_die cycles if cycles_to_die > 0.
        // After it's value becomes less than 1, the check is performed each cycle.
        if (vm->ctd <= 0 || vm->cycles == vm->ctd)
            perform_check(vm);
            
        // check flag -dump
        // At the end of nbr_cycles of executions, dump the memory on the standard output and quit the game.
        // The memory must be dumped in the hexadecimal format with 32 octets per line.
        /*
        if (vm->current_cycle == vm->dump_cycle)
			dump(vm);
        */
    }
}