/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 11:00:28 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/30 11:10:17 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void print_player1(WINDOW *win)
{
    wattron(win, COLOR_PAIR(GREEN) | A_BOLD);
	mvwprintw(win, 2, 4, "%ls", PL1_1);
	mvwprintw(win, 3, 4, "%ls", PL1_2);
	mvwprintw(win, 4, 4, "%ls", PL1_3);
	mvwprintw(win, 5, 4, "%ls", PL1_4);
    wattroff(win, COLOR_PAIR(GREEN) | A_BOLD);
}

static void print_player2(WINDOW *win)
{
    wattron(win, COLOR_PAIR(B_B) | A_BOLD);
	mvwprintw(win, 7, 4, "%ls", PL2_1);
	mvwprintw(win, 8, 4, "%ls", PL2_2);
	mvwprintw(win, 9, 4, "%ls", PL2_3);
	mvwprintw(win, 10, 4, "%ls", PL2_4);
    wattroff(win, COLOR_PAIR(B_B) | A_BOLD);
}

static void print_player3(WINDOW *win)
{
    wattron(win, COLOR_PAIR(Y_B) | A_BOLD);
	mvwprintw(win, 12, 4, "%ls", PL3_1);
	mvwprintw(win, 13, 4, "%ls", PL3_2);
	mvwprintw(win, 14, 4, "%ls", PL3_3);
	mvwprintw(win, 15, 4, "%ls", PL3_4);
    wattroff(win, COLOR_PAIR(Y_B) | A_BOLD);
}

static void print_player4(WINDOW *win)
{
    wattron(win, COLOR_PAIR(R_B) | A_BOLD);
	mvwprintw(win, 17, 4, "%ls", PL4_1);
	mvwprintw(win, 18, 4, "%ls", PL4_2);
	mvwprintw(win, 19, 4, "%ls", PL4_3);
	mvwprintw(win, 20, 4, "%ls", PL4_4);
	wattroff(win, COLOR_PAIR(R_B) | A_BOLD);
}                     

void print_players(t_vm *vm, WINDOW *win)
{
    int i;

	i = -1;
	while (vm->p[++i].id)
    {
		if (i == 0)
            print_player1(win);
        else if (i == 1)
            print_player2(win);
        else if (i == 2)
            print_player3(win);
        else if (i == 3)
            print_player4(win);
    }
	wrefresh(win);
}
