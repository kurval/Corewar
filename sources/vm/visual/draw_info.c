/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 19:24:46 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/01 08:46:20 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void print_info(t_vm *vm, t_player *player, int y, int x)
{
    wattron(vm->visu->side2, COLOR_PAIR(player->id) | A_BOLD);
    mvwprintw(vm->visu->side2, y, x + 46, "%s", player->h.prog_name);
    wattron(vm->visu->side2, COLOR_PAIR(W_B) | A_BOLD);
    mvwprintw(vm->visu->side2, y++, x + 40, "Name: ");
    mvwprintw(vm->visu->side2, y++, x + 40, "Last live: %d", player->last_live);
    mvwprintw(vm->visu->side2, y++, x + 40, "Period lives: %d", player->period_lives);
    wattroff(vm->visu->side2, COLOR_PAIR(W_B) | A_BOLD);
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
    mvwprintw(win, y + 3, x, "CYCLE_TO_DIE: %d", vm->ctd);
    mvwprintw(win, y + 3, x + 30, "NBR_LIVE: %d", NBR_LIVE);
    mvwprintw(win, y + 6, x, "CYCLE_DELTA: %d", CYCLE_DELTA);
    mvwprintw(win, y + 6, x + 30, "MAX_CHECKS: %d", MAX_CHECKS);
    wattroff(win, COLOR_PAIR(W_B) | A_BOLD);
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
    print_battle_info(vm, 10, 4);
    box_win(vm->visu->side3);
	wrefresh(win);
}