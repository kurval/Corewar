/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_logo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:04:30 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/01 17:53:54 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void print_pause(WINDOW *win)
{
    wattron(win, COLOR_PAIR(W_B));
	mvwprintw(win, 13, 30, "**PAUSED**");
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
    if (!vm->visu->running)
        print_pause(win);
    box_win(win);
	wrefresh(win);
}
