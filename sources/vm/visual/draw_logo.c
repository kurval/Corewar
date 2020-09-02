/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_logo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:04:30 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/02 16:20:56 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void print_mode_text(t_vm *vm)
{
	WINDOW *win;
	int max_y;
	int max_x;

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

void draw_logo(t_vm *vm)
{
    WINDOW *win;

    win = vm->visu->side1;
    werase(win);
	wattron(win, COLOR_PAIR(R_B));
	mvwprintw(win, 3, 4, "%ls", LOGO1);
	mvwprintw(win, 4, 4, "%ls", LOGO2);
	mvwprintw(win, 5, 4, "%ls", LOGO3);
	mvwprintw(win, 6, 4, "%ls", LOGO4);
	mvwprintw(win, 7, 4, "%ls", LOGO5);
	mvwprintw(win, 8, 4, "%ls", LOGO6);
	mvwprintw(win, 9, 4, "%ls", LOGO7);
	mvwprintw(win, 10, 4, "%ls", LOGO8);
	mvwprintw(win, 11, 4, "%ls", LOGO9);
	mvwprintw(win, 12, 4, "%ls", LOGO10);
	wattroff(win, COLOR_PAIR(R_B));
    print_mode_text(vm);
    box_win(win);
	wrefresh(win);
}
