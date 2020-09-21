/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_battle_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:41:06 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/21 17:24:12 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	print_battle_banner(WINDOW *win, int y, int x)
{
	mvwprintw(win, y++, x, "%ls", B1);
	mvwprintw(win, y++, x, "%ls", B2);
	mvwprintw(win, y++, x, "%ls", B3);
	mvwprintw(win, y++, x, "%ls", B4);
	mvwprintw(win, y++, x, "%ls", B5);
}

static void	print_speed_blocks(WINDOW *win, int speed, int y, int x)
{
	speed == 0 ? mvwprintw(win, y, x, "%ls", S1) : 0;
	speed == 1 ? mvwprintw(win, y, x, "%ls", S2) : 0;
	speed == 2 ? mvwprintw(win, y, x, "%ls", S3) : 0;
	speed == 3 ? mvwprintw(win, y, x, "%ls", S4) : 0;
	speed == 4 ? mvwprintw(win, y, x, "%ls", S5) : 0;
	speed == 5 ? mvwprintw(win, y, x, "%ls", S6) : 0;
	speed == 6 ? mvwprintw(win, y, x, "%ls", S7) : 0;
	speed == 7 ? mvwprintw(win, y, x, "%ls", S8) : 0;
	speed == 8 ? mvwprintw(win, y, x, "%ls", S9) : 0;
	speed == 9 ? mvwprintw(win, y, x, "%ls", S10) : 0;
	speed == 10 ? mvwprintw(win, y, x, "%ls", S11) : 0;
}

static void	print_speed(t_vm *vm, int y, int x)
{
	int		speed;
	WINDOW	*win;

	win = vm->visu->side3;
	speed = vm->visu->speed / 10000;
	wattron(win, COLOR_PAIR(M_B) | A_BOLD);
	print_speed_blocks(win, speed, y + 7, x + 8);
	wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
}

static void	print_battle_info(t_vm *vm, WINDOW *win, int y, int x)
{
	wattron(win, COLOR_PAIR(M_B) | A_BOLD);
	mvwprintw(win, y, x, "CYCLES: ");
	mvwprintw(win, y, x + 30, "PROCESSES: ");
	mvwprintw(win, y + 10, x, "--> ");
	mvwprintw(win, y + 11, x, "--> ");
	mvwprintw(win, y + 12, x, "--> ");
	mvwprintw(win, y + 13, x, "--> ");
	wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
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
	wattroff(win, COLOR_PAIR(W_B) | A_BOLD);
}

void		draw_battle_info(t_vm *vm)
{
	WINDOW	*win;

	win = vm->visu->side3;
	werase(win);
	wattron(win, COLOR_PAIR(M_B) | A_BOLD);
	print_battle_banner(win, 2, 4);
	wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
	print_battle_info(vm, win, 9, 4);
	print_speed(vm, 9, 4);
	box_win(vm->visu->side3);
	wrefresh(win);
}
