/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 11:00:28 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/01 06:38:31 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void print_player1(t_vm *vm, int height, int weidth)
{
    int y;
    int x;

    y = height;
    x = weidth;
    wattron(vm->visu->side2, COLOR_PAIR(GREEN) | A_BOLD);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL1_1);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL1_2);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL1_3);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL1_4);
    wattroff(vm->visu->side2, COLOR_PAIR(GREEN) | A_BOLD);
}

void print_player2(t_vm *vm, int height, int weidth)
{
    int y;
    int x;

    y = height;
    x = weidth;
    wattron(vm->visu->side2, COLOR_PAIR(B_B) | A_BOLD);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL2_1);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL2_2);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL2_3);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL2_4);
    wattroff(vm->visu->side2, COLOR_PAIR(B_B) | A_BOLD);
}

void print_player3(t_vm *vm, int height, int weidth)
{
    int y;
    int x;

    y = height;
    x = weidth;
    wattron(vm->visu->side2, COLOR_PAIR(Y_B) | A_BOLD);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL3_1);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL3_2);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL3_3);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL3_4);
    wattroff(vm->visu->side2, COLOR_PAIR(Y_B) | A_BOLD);
}

void print_player4(t_vm *vm, int height, int weidth)
{
    int y;
    int x;

    y = height;
    x = weidth;
    wattron(vm->visu->side2, COLOR_PAIR(R_B) | A_BOLD);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL4_1);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL4_2);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL4_3);
	mvwprintw(vm->visu->side2, y++, x, "%ls", PL4_4);
	wattroff(vm->visu->side2, COLOR_PAIR(R_B) | A_BOLD);
}                     

void draw_players(t_vm *vm)
{
    unsigned int i;
    WINDOW *win;

	i = -1;
    win = vm->visu->side2;
	while (++i < vm->nb_players)
    {
		if (i == 0)
            print_player1(vm, 2, 4);
        else if (i == 1)
            print_player2(vm, 7, 4);
        else if (i == 2)
            print_player3(vm, 12, 4);
        else if (i == 3)
            print_player4(vm, 17, 4);
    }
    print_player_info(vm);
    box_win(win);
	wrefresh(win);
}
