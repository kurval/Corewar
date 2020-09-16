/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 11:05:40 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/16 11:53:50 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	print_debug_info(t_vm *vm)
{
	WINDOW * win;
	win = vm->visu->side2;
	wattron(win, COLOR_PAIR(W_B));
	mvwprintw(win, 1, 1, "** HIT SPACE TO DEBUG **\n");
	wattroff(win, COLOR_PAIR(W_B));
}

static void	print_operation(t_vm *vm, t_process *proc)
{
	int	color;

	WINDOW * win;
	win = vm->visu->side2;
	color = (proc->opcode == 1) ? vm->p[vm->visu->live_id].id : W_B;
	wattron(win, COLOR_PAIR(Y_B) | A_BOLD);
	wprintw(win, "[CURSOR ID %6d] ", proc->id);
	wattroff(win, COLOR_PAIR(Y_B) | A_BOLD);
	wattron(win, COLOR_PAIR(color) | A_BOLD);
	if (proc->opcode == 1)
		wprintw(win, "%s is alive\n", vm->p[vm->visu->live_id].h.prog_name);
	else
		wprintw(win, "executed %s\n",\
		vm->operations[proc->opcode - 1].instr_name);
	wattroff(win, COLOR_PAIR(color) | A_BOLD);
}

void		log_operation(t_vm *vm, t_process *proc)
{
	int		y;
	int		x;

	WINDOW * win;
	win = vm->visu->side2;
	vm->visu->log_count++;
	getyx(win, y, x);
	wmove(win, y, x + 1);
	wattron(win, COLOR_PAIR(M_B) | A_BOLD);
	wprintw(win, "[CYCLE %5d] ", vm->current_cycle);
	wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
	if (vm->visu->log_count == 0)
	{
		wattron(win, COLOR_PAIR(GRAY_B) | A_BOLD);
		wprintw(win, "[NOTHING HAPPENED]\n");
		wattroff(win, COLOR_PAIR(GRAY_B) | A_BOLD);
		return ;
	}
	else
		print_operation(vm, proc);
}

void		draw_log(t_vm *vm)
{
	WINDOW * win;
	win = vm->visu->side2;
	scrollok(win, TRUE);
	if (vm->visu->log_count == 0)
	{
		vm->visu->log_count = -1;
		log_operation(vm, vm->proc_list);
	}
	else
		vm->visu->log_count = 0;
	box_win(win);
	wrefresh(win);
}

void		set_debug(t_vm *vm)
{
	vm->visu->debug = (!vm->visu->debug);
	if (vm->visu->debug)
	{
		werase(vm->visu->side2);
		print_debug_info(vm);
	}
}
