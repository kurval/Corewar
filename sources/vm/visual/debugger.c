/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 11:05:40 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/14 14:24:13 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	print_debug_info(t_vm *vm)
{
	int		max_y;
	int		max_x;

	WINDOW * win;
	win = vm->visu->side2;
	getmaxyx(win, max_y, max_x);
	wattron(win, COLOR_PAIR(W_B));
	mvwprintw(win, 1, 1, "** HIT SPACE TO DEBUG **\n");
	wattroff(win, COLOR_PAIR(W_B));
}

void		log_operation(t_vm *vm, t_process *proc, int i)
{
	char	*log;

	log = NULL;
	vm->visu->log_count++;
	if (proc->opcode == 1)
	{
		if (!(log = ft_strjoin(vm->p[i].h.prog_name, " is a")))
			ft_errno(MALLOC_ERROR);
		print_log_text(vm, proc, log, vm->p[i].id);
		free(log);
	}
	else
		print_log_text(vm, proc, "executed ", i);
}

void		print_log_text(t_vm *vm, t_process *proc, char *str, int color_num)
{
	int		y;
	int		x;

	WINDOW * win;
	win = vm->visu->side2;
	getyx(win, y, x);
	wmove(win, y, x + 1);
	wattron(win, COLOR_PAIR(M_B) | A_BOLD);
	wprintw(win, "[CYCLE %8d] ", vm->current_cycle);
	wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
	if (vm->visu->log_count == 0)
	{
		wattron(win, COLOR_PAIR(GRAY_B) | A_BOLD);
		wprintw(win, "[NOTHING HAPPENED]\n");
		wattroff(win, COLOR_PAIR(GRAY_B) | A_BOLD);
		return ;
	}
	wattron(win, COLOR_PAIR(Y_B) | A_BOLD);
	wprintw(win, "[PROC ID %8d] ", proc->id);
	wattroff(win, COLOR_PAIR(Y_B) | A_BOLD);
	wattron(win, COLOR_PAIR(color_num) | A_BOLD);
	wprintw(win, "%s%s\n", str, vm->operations[proc->opcode - 1].instr_name);
	wattroff(win, COLOR_PAIR(color_num) | A_BOLD);
}

void		draw_log(t_vm *vm)
{
	WINDOW * win;
	win = vm->visu->side2;
	scrollok(win, TRUE);
	if (vm->visu->log_count == 0)
		print_log_text(vm, vm->proc_list, NULL, Y_B);
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
