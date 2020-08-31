/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_banners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 17:17:49 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/31 19:14:20 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void	draw_footer(t_vm *vm)
{
    WINDOW *win;

    win = vm->visu->side4;
    box_win(win);
	wattron(win, COLOR_PAIR(W_B) | A_BOLD);
	mvwprintw(win, 2, 4, "BY: ATUOMINE | JEMETELIN | BKONJUHA | VKURKELA 2020");
	wattroff(win, COLOR_PAIR(W_B) | A_BOLD);
	wrefresh(win);
}
                                                                                                                                                                