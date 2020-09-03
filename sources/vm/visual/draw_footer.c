/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_footer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 17:17:49 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/03 12:33:50 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void	draw_footer(t_vm *vm)
{
	int	max_y;
	int	max_x;

	WINDOW * win;
	max_y = 0;
	max_x = 0;
	win = vm->visu->side1;
	getmaxyx(win, max_y, max_x);
	win = vm->visu->side4;
	wattron(win, COLOR_PAIR(W_B) | A_BOLD);
	mvwprintw(win, 2, (max_x / 2) - (56 / 2),\
			"{ BY: ATUOMINE | JEMETELIN | BKONJUHA | VKURKELA 2020 }");
	wattroff(win, COLOR_PAIR(W_B) | A_BOLD);
	box_win(win);
	wrefresh(win);
}
