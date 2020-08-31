/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_winner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:35:07 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/31 19:32:02 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void print_win(WINDOW *win, int height, int weidth)
{
    int y;
    int x;

    y = height;
    x = weidth;
    wattron(win, COLOR_PAIR(Y_B) | A_BLINK);
	mvwprintw(win, y++, x, "%ls", WIN1);
	mvwprintw(win, y++, x, "%ls", WIN2);
    mvwprintw(win, y++, x, "%ls", WIN3);
    mvwprintw(win, y++, x, "%ls", WIN4);
    mvwprintw(win, y++, x, "%ls", WIN5);
    mvwprintw(win, y++, x, "%ls", WIN6);
    wattroff(win, COLOR_PAIR(Y_B) | A_BLINK);
}

void    print_winner(t_vm *vm)
{
    WINDOW *win;

    win = vm->visu->side2;
    vm->last_live_id = 3;
    werase(win);
    box_win(win);
    if (vm->last_live_id == 1)
        print_player1(vm, 6, 4);
    else if (vm->last_live_id == 2)
        print_player2(vm, 6, 4);
    else if (vm->last_live_id == 3)
        print_player3(vm, 6, 4);
    else if (vm->last_live_id == 4)
        print_player4(vm, 6, 4);
    print_win(win, 13, 4);
    print_info(vm, &vm->p[vm->last_live_id - 1], 7, 4);
    wrefresh(win);
}
