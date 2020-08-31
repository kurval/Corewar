/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 19:24:46 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/31 13:11:05 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void print_battle_info(t_vm *vm, int y, int x)
{
    wattron(vm->visu->side3, COLOR_PAIR(M_B) | A_BOLD);
    mvwprintw(vm->visu->side3, y, x, "CYCLES: ");
    mvwprintw(vm->visu->side3, y, x + 30, "PROCESSES: ");
    wattron(vm->visu->side3, COLOR_PAIR(W_B) | A_BOLD);
    mvwprintw(vm->visu->side3, y, x + 8, "%d", vm->cycles);
    mvwprintw(vm->visu->side3, y, x + 41, "%d", vm->nb_procs);
    mvwprintw(vm->visu->side3, y + 3, x, "CYCLE_TO_DIE: %d", CYCLE_TO_DIE);
    mvwprintw(vm->visu->side3, y + 3, x + 30, "NBR_LIVE: %d", NBR_LIVE);
    mvwprintw(vm->visu->side3, y + 6, x, "CYCLE_DELTA: %d", CYCLE_DELTA);
    mvwprintw(vm->visu->side3, y + 6, x + 30, "MAX_CHECKS: %d", MAX_CHECKS);
    wattroff(vm->visu->side3, COLOR_PAIR(W_B) | A_BOLD);
    wrefresh(vm->visu->side3);
}

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
    wrefresh(vm->visu->side2);
}