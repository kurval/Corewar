/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_logo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:04:30 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/12 15:39:24 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	print_logo(WINDOW *win, int y, int x)
{
	mvwprintw(win, y++, x, "%ls", L1);
	mvwprintw(win, y++, x, "%ls", L2);
	mvwprintw(win, y++, x, "%ls", L3);
	mvwprintw(win, y++, x, "%ls", L4);
	mvwprintw(win, y++, x, "%ls", L5);
	mvwprintw(win, y++, x, "%ls", L6);
	mvwprintw(win, y++, x, "%ls", L7);
	mvwprintw(win, y++, x, "%ls", L8);
	mvwprintw(win, y++, x, "%ls", L9);
	mvwprintw(win, y++, x, "%ls", L10);
}

static void	print_mode_text(t_vm *vm)
{
	int		max_y;
	int		max_x;
	WINDOW	*win;

	max_y = 0;
	max_x = 0;
	win = vm->visu->side1;
	getmaxyx(win, max_y, max_x);
	wattron(win, COLOR_PAIR(W_B));
	if (vm->visu->debug)
		mvwprintw(win, 13, (max_x / 2) - (16 / 2), "** DEBUG MODE **");
	else if (!vm->visu->running)
		mvwprintw(win, 13, (max_x / 2) - (12 / 2), "** PAUSED **");
	else
		mvwprintw(win, 13, (max_x / 2) - (13 / 2), "** RUNNING **");
	wattroff(win, COLOR_PAIR(W_B));
}

void		draw_logo(t_vm *vm)
{
	WINDOW	*win;

	win = vm->visu->side1;
	werase(win);
	wattron(win, COLOR_PAIR(R_B));
	print_logo(win, 3, 4);
	wattroff(win, COLOR_PAIR(R_B));
	print_mode_text(vm);
	box_win(win);
	wrefresh(win);
}
