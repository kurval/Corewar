/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_logo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:04:30 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/31 19:31:42 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void draw_logo(t_vm *vm)
{
    WINDOW *win;

    win = vm->visu->side1;
    box_win(win);
	wattron(win, COLOR_PAIR(R_B));
	mvwprintw(win, 3, 6, "%ls", LOGO1);
	mvwprintw(win, 4, 6, "%ls", LOGO2);
	mvwprintw(win, 5, 6, "%ls", LOGO3);
	mvwprintw(win, 6, 6, "%ls", LOGO4);
	mvwprintw(win, 7, 6, "%ls", LOGO5);
	mvwprintw(win, 8, 6, "%ls", LOGO6);
	mvwprintw(win, 9, 6, "%ls", LOGO7);
	mvwprintw(win, 10, 6, "%ls", LOGO8);
	mvwprintw(win, 11, 6, "%ls", LOGO9);
	mvwprintw(win, 12, 6, "%ls", LOGO10);
	wattroff(win, COLOR_PAIR(R_B));
	wrefresh(win);
}
