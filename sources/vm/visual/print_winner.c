/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_winner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:35:07 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/12 15:32:26 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	print_trophy(WINDOW *win, int y, int x)
{
	mvwprintw(win, y++, x, "%ls", T1);
	mvwprintw(win, y++, x, "%ls", T2);
	mvwprintw(win, y++, x, "%ls", T3);
	mvwprintw(win, y++, x, "%ls", T4);
	mvwprintw(win, y++, x, "%ls", T5);
	mvwprintw(win, y++, x, "%ls", T6);
	mvwprintw(win, y++, x, "%ls", T7);
	mvwprintw(win, y++, x, "%ls", T8);
}

static void	print_win(WINDOW *win, int y, int x)
{
	mvwprintw(win, y++, x, "%ls", WIN1);
	mvwprintw(win, y++, x, "%ls", WIN2);
	mvwprintw(win, y++, x, "%ls", WIN3);
	mvwprintw(win, y++, x, "%ls", WIN4);
	mvwprintw(win, y++, x, "%ls", WIN5);
	mvwprintw(win, y++, x, "%ls", WIN6);
}

static void	print_win_banner(WINDOW *win, int winner)
{
	wattron(win, COLOR_PAIR(Y_B) | A_BLINK);
	print_win(win, 10, 4);
	print_trophy(win, 9, 38);
	wattroff(win, COLOR_PAIR(winner) | A_BLINK);
	wattron(win, COLOR_PAIR(W_B) | A_BOLD);
	mvwprintw(win, 18, 4, "PRESS ANY KEY TO FINISH");
	wattroff(win, COLOR_PAIR(W_B) | A_BOLD);
}

static void	print_winner_name(t_vm *vm, WINDOW *win, int winner)
{
	wattron(win, COLOR_PAIR(winner) | A_BOLD);
	if (winner == 1)
		print_player1(vm, 4, 4);
	else if (winner == 2)
		print_player2(vm, 4, 4);
	else if (winner == 3)
		print_player3(vm, 4, 4);
	else if (winner == 4)
		print_player4(vm, 4, 4);
	wattroff(win, COLOR_PAIR(winner) | A_BOLD);
}

void		print_winner(t_vm *vm)
{
	WINDOW	*win;
	int		winner;

	win = vm->visu->side2;
	winner = vm->last_live_id;
	werase(win);
	print_winner_name(vm, win, winner);
	print_win_banner(win, winner);
	print_info(vm, &vm->p[vm->last_live_id - 1], 5, 4);
	box_win(win);
	wrefresh(win);
}
