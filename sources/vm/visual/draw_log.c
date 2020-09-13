/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 11:05:40 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/13 20:54:28 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void	log_operation(t_vm *vm, t_process *proc, char *str, int i)
{
	char	*log;
	char	*proc_id;

	log = NULL;
	proc_id = NULL;
	if (proc->opcode == 1)
	{
		if (!(log = ft_strjoin(vm->p[i].h.prog_name,\
						str)))
			ft_errno(MALLOC_ERROR);
		print_log_text(vm, log, vm->p[i].id);
		free(log);
	}
	else
	{
		proc_id = ft_itoa(proc->id);
		log = ft_strjoin(proc_id, str);
		print_log_text(vm, log, i);
		free(proc_id);
		free(log);
	}
}

void	print_log_text(t_vm *vm, char *str, int color_num)
{
	int		y;
	int		x;

	WINDOW * win;
	win = vm->visu->side2;
	getyx(win, y, x);
	wmove(win, y, x + 1);
	wattron(win, COLOR_PAIR(M_B) | A_BOLD);
	wprintw(win, "[CYCLE %d] ", vm->current_cycle);
	wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
	wattron(win, COLOR_PAIR(color_num) | A_BOLD);
	wmove(win, y, x + (ft_numlen(vm->current_cycle) + 10));
	wprintw(win, str);
	wattroff(win, COLOR_PAIR(color_num) | A_BOLD);
}

void	draw_log(t_vm *vm)
{
	WINDOW * win;
	win = vm->visu->side2;
	scrollok(win, TRUE);
	box_win(win);
	wrefresh(win);
}
