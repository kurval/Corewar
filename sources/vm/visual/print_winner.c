/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_winner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:35:07 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/03 18:02:01 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	print_trophy(WINDOW *win, int height, int weidth)
{
	int y;
	int x;

	y = height;
	x = weidth;
	wattron(win, COLOR_PAIR(Y_B) | A_BLINK);
	mvwprintw(win, y++, x, "%ls", T1);
	mvwprintw(win, y++, x, "%ls", T2);
	mvwprintw(win, y++, x, "%ls", T3);
	mvwprintw(win, y++, x, "%ls", T4);
	mvwprintw(win, y++, x, "%ls", T5);
	mvwprintw(win, y++, x, "%ls", T6);
	mvwprintw(win, y++, x, "%ls", T7);
	mvwprintw(win, y++, x, "%ls", T8);
	wattroff(win, COLOR_PAIR(Y_B) | A_BLINK);
}

static void	print_win(WINDOW *win, int height, int weidth)
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
	wattron(win, COLOR_PAIR(W_B) | A_BLINK);
	mvwprintw(win, y + 2, x, "PRESS ANY KEY TO FINISH");
	wattroff(win, COLOR_PAIR(W_B) | A_BLINK);
}

void		print_winner(t_vm *vm)
{
	int		winner;
	WINDOW	*win;

	win = vm->visu->side2;
	winner = vm->last_live_id;
	werase(win);
	if (winner == 1)
		print_player1(vm, 4, 4, winner);
	else if (winner == 2)
		print_player2(vm, 4, 4, winner);
	else if (winner == 3)
		print_player3(vm, 4, 4, winner);
	else if (winner == 4)
		print_player4(vm, 4, 4, winner);
	print_win(win, 10, 4);
	print_trophy(win, 9, 38);
	print_info(vm, &vm->p[vm->last_live_id - 1], 5, 4);
	box_win(win);
	wrefresh(win);
}
