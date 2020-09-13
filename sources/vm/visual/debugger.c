/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 11:05:40 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/13 22:44:54 by vkurkela         ###   ########.fr       */
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

void		log_operation(t_vm *vm, t_process *proc, char *str, int i)
{
	char	*log;

	log = NULL;
	if (proc->opcode == 1)
	{
		if (!(log = ft_strjoin(vm->p[i].h.prog_name,\
						str)))
			ft_errno(MALLOC_ERROR);
		print_log_text(vm, proc, log, vm->p[i].id);
		free(log);
	}
	else
		print_log_text(vm, proc, str, i);
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
	wattron(win, COLOR_PAIR(GRAY_B) | A_BOLD);
	wprintw(win, "[PROC ID %6d] ", proc->id);
	wattroff(win, COLOR_PAIR(GRAY_B) | A_BOLD);
	wattron(win, COLOR_PAIR(color_num) | A_BOLD);
	wprintw(win, str);
	wattroff(win, COLOR_PAIR(color_num) | A_BOLD);
}

void		draw_log(t_vm *vm)
{
	WINDOW * win;
	win = vm->visu->side2;
	scrollok(win, TRUE);
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
