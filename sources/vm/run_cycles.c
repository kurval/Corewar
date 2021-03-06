/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cycles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 11:31:36 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/16 21:33:23 by vkurkela         ###   ########.fr       */
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

static void	set_opcode(t_vm *vm, t_process *proc)
{
	proc->opcode = vm->a->arena[proc->pc];
	if (proc->opcode && proc->opcode <= REG_NUMBER)
		proc->wait_cycles = vm->operations[proc->opcode - 1].wait_cycles;
	else
		proc->wait_cycles = 1;
}

/*
** If wait_cycles == 0 it's time to execute the operation, that is saved in the
** cursor.
** - If saved operation code is a valid code and operation requires encoding
**   byte, validate it.
** - If encoding byte is valid and there are registries among the arguments,
**   validate registry numbers.
** - If all the checks were successfully passed, execute the operation and move
**   cursor to the next operation.
** - If operation code is not valid, move cursor to the next byte.
** - If operation code is valid, but encoding byte is invalid or one of
**   arguments is not valid.
**  >Cursor must be moved to the next operation without execution.
** To get to the next operation, cursor must skip operation byte, encoding byte
** (if present),
** and arguments saved in the encoding byte.
*/

static void	execute_operation(t_vm *vm, t_process *proc)
{
	!proc->wait_cycles ? set_opcode(vm, proc) : 0;
	proc->wait_cycles -= 1;
	if (!proc->wait_cycles)
	{
		if (proc->opcode && proc->opcode <= REG_NUMBER)
		{
			if (get_args(vm, proc))
				vm->operations[proc->opcode - 1].f(vm, proc);
		}
		else
			proc->jump = 1;
		proc->pc = get_addr(proc->pc + proc->jump);
	}
	vm->v_flag ? vm->visu->attributes[proc->pc].cursor = true : 0;
}

/*
** During the check dead cursors are removed from the list.
** Cursor is considered dead, if it performed operation
** live more than cycles_to_die or more cycles ago.
** Also, if cycles_to_die <= 0 all carriages are considered dead.
*/

static void	check_dead_processes(t_vm *vm, t_process **proc_list)
{
	t_process *current;
	t_process *previous;

	current = *proc_list;
	previous = NULL;
	while (current)
	{
		if (current->last_live <= vm->current_cycle - vm->ctd ||\
		vm->ctd <= 0)
			remove_proc(vm, proc_list, &current, &previous);
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

/*
** If during last cycles_to_die cycles operation live was performed
** NBR_LIVE times or more, cycles_to_die is decreased with CYCLE_DELTA.
** If after MAX_CHECKS checks cycles_to_die was not changed, it gets decreased.
** Also reset period counter and lives performed in current period.
*/

static void	perform_check(t_vm *vm, t_process **proc_list)
{
	unsigned int i;

	i = -1;
	vm->checks++;
	check_dead_processes(vm, proc_list);
	if (vm->lives >= NBR_LIVE || vm->checks >= MAX_CHECKS)
	{
		vm->ctd -= CYCLE_DELTA;
		vm->checks = 0;
	}
	vm->cycles = 0;
	vm->lives = 0;
	while (++i < vm->nb_players)
		vm->p[i].period_lives = 0;
}

/*
** This is the battle function which continues as long as there are processes
** left.
** - We go through list of cursors in every cycle to determine if statement
**   should be executed.
** - The check is performed once in cycles_to_die cycles if cycles_to_die > 0.
**  >After it's value becomes less than 1, the check is performed each cycle.
** - If -dump flag is present The memory must be dumped in the hexadecimal
**  >format with 32 octets per line.
*/

void		run_cycles(t_vm *vm)
{
	t_process *current;

	while ((current = vm->proc_list))
	{
		vm->current_cycle++;
		vm->cycles++;
		while (current)
		{
			execute_operation(vm, current);
			current = current->next;
		}
		if (vm->ctd <= 0 || vm->cycles == (unsigned int)vm->ctd)
			perform_check(vm, &vm->proc_list);
		if ((int)vm->current_cycle == vm->dump_cycle)
			dump_memory(vm);
		else if ((int)vm->current_cycle == vm->d_flag)
			print_arena(vm);
		else if (vm->v_flag)
			manage_windows(vm, getch());
	}
	if (vm->v_flag)
		vm->visu->end = true;
}
