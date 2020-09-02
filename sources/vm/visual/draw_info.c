/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 19:24:46 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/02 14:59:33 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void print_speed(t_vm *vm, int y, int x)
{
    int speed;
    WINDOW *win;

    win = vm->visu->side3;
    speed = vm->visu->speed / 10000;
    wattron(win, COLOR_PAIR(M_B) | A_BOLD);
    speed == 0 ? mvwprintw(win, y + 7, x + 8, "%ls", S1) : 0;
    speed == 1 ? mvwprintw(win, y + 7, x + 8, "%ls", S2) : 0;
    speed == 2 ? mvwprintw(win, y + 7, x + 8, "%ls", S3) : 0;
    speed == 3 ? mvwprintw(win, y + 7, x + 8, "%ls", S4) : 0;
    speed == 4 ? mvwprintw(win, y + 7, x + 8, "%ls", S5) : 0;
    speed == 5 ? mvwprintw(win, y + 7, x + 8, "%ls", S6) : 0;
    speed == 6 ? mvwprintw(win, y + 7, x + 8, "%ls", S7) : 0;
    speed == 7 ? mvwprintw(win, y + 7, x + 8, "%ls", S8) : 0;
    speed == 8 ? mvwprintw(win, y + 7, x + 8, "%ls", S9) : 0;
    speed == 9 ? mvwprintw(win, y + 7, x + 8, "%ls", S10) : 0;
    speed == 10 ? mvwprintw(win, y + 7, x + 8, "%ls", S11) : 0;
    wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
}

void print_info(t_vm *vm, t_player *player, int y, int x)
{
    WINDOW *win;

    win = vm->visu->side2;
    wattron(win, COLOR_PAIR(player->id) | A_BOLD);
    mvwprintw(win, y, x + 46, "%s", player->h.prog_name);
    wattron(win, COLOR_PAIR(W_B) | A_BOLD);
    mvwprintw(win, y++, x + 40, "Name: ");
    mvwprintw(win, y++, x + 40, "Last live: %d", player->last_live);
    mvwprintw(win, y++, x + 40, "Period lives: %d", player->period_lives);
    wattroff(win, COLOR_PAIR(W_B) | A_BOLD);
}

void    print_player_info(t_vm *vm)
{
    unsigned int i;
    int x;
    int y;

	i = -1;
    y = 3;
    x = 4;
	while (++i < vm->nb_players)
    {
        print_info(vm, &vm->p[i], y, x);
        y += 5;
    }
}

static void print_battle_info(t_vm *vm, int y, int x)
{
    WINDOW *win;

    win = vm->visu->side3;
    wattron(win, COLOR_PAIR(M_B) | A_BOLD);
    mvwprintw(win, y, x, "CYCLES: ");
    mvwprintw(win, y, x + 30, "PROCESSES: ");
    wattron(win, COLOR_PAIR(W_B) | A_BOLD);
    mvwprintw(win, y, x + 8, "%d", vm->current_cycle);
    mvwprintw(win, y, x + 41, "%d", vm->nb_procs);
    mvwprintw(win, y + 2, x, "CYCLE_TO_DIE: %d", vm->ctd);
    mvwprintw(win, y + 2, x + 30, "NBR_LIVE: %d", NBR_LIVE);
    mvwprintw(win, y + 4, x, "CYCLE_DELTA: %d", CYCLE_DELTA);
    mvwprintw(win, y + 4, x + 30, "MAX_CHECKS: %d", MAX_CHECKS);
    mvwprintw(win, y + 7, x, "SPEED: ");
    mvwprintw(win, y + 10, x + 4, "Press '<-' or '->' to adjust speed");
    mvwprintw(win, y + 11, x + 4, "Press SPACE to pause");
    mvwprintw(win, y + 12, x + 4, "Press 'd' to debug");
    mvwprintw(win, y + 13, x + 4, "Press ESC to quit");
    wattron(win, COLOR_PAIR(M_B) | A_BOLD);
    mvwprintw(win, y + 10, x, "--> ");
    mvwprintw(win, y + 11, x, "--> ");
    mvwprintw(win, y + 12, x, "--> ");
    mvwprintw(win, y + 13, x, "--> ");
    wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
    print_speed(vm, y, x);
}

void	draw_battle_info(t_vm *vm)
{
    WINDOW *win;

    win = vm->visu->side3;
    werase(win);
	wattron(win, COLOR_PAIR(M_B) | A_BOLD);
	mvwprintw(win, 2, 4, "%ls", BI1);
	mvwprintw(win, 3, 4, "%ls", BI2);
	mvwprintw(win, 4, 4, "%ls", BI3);
	mvwprintw(win, 5, 4, "%ls", BI4);
	mvwprintw(win, 6, 4, "%ls", BI5);
	wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
    print_battle_info(vm, 9, 4);
    box_win(vm->visu->side3);
	wrefresh(win);
}