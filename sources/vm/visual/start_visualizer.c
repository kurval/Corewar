/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visualizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:50:02 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/31 11:43:58 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	signature(WINDOW *win)
{
	wattron(win, COLOR_PAIR(W_B) | A_BOLD);
	mvwprintw(win, 2, 4, "BY: ATUOMINE | JEMETELIN | BKONJUHA | VKURKELA 2020");
	wattroff(win, COLOR_PAIR(W_B) | A_BOLD);
	wrefresh(win);
}

static void	battle_info(WINDOW *win)
{
	wattron(win, COLOR_PAIR(M_B) | A_BOLD);
	mvwprintw(win, 2, 4, "%ls", BI1);
	mvwprintw(win, 3, 4, "%ls", BI2);
	mvwprintw(win, 4, 4, "%ls", BI3);
	mvwprintw(win, 5, 4, "%ls", BI4);
	mvwprintw(win, 6, 4, "%ls", BI5);
	wattroff(win, COLOR_PAIR(M_B) | A_BOLD);
	wrefresh(win);
}
                                                                                                                                                                  
static void print_logo(WINDOW *win)
{
	wattron(win, COLOR_PAIR(R_B));
	mvwprintw(win, 3, 6, "%ls", LOGO1);
	mvwprintw(win, 4, 6, "%ls", LOGO2);
	mvwprintw(win, 5, 6, "%ls", LOGO3);
	mvwprintw(win, 6, 6, "%ls", LOGO4);
	mvwprintw(win, 7, 6, "%ls", LOGO5);
	mvwprintw(win, 8, 6, "%ls", LOGO6);
	mvwprintw(win, 9, 6, "%ls", LOGO7);
	mvwprintw(win, 10, 6, "%ls", LOGO8);
	mvwprintw(win, 11, 6, "%ls", LOGO9);
	mvwprintw(win, 12, 6, "%ls", LOGO10);
	wattroff(win, COLOR_PAIR(R_B));
	wrefresh(win);
}

void	box_win(WINDOW *win)
{
	wattron(win, COLOR_PAIR(FRAME));
	box(win, 0, '*');
	wattroff(win, COLOR_PAIR(FRAME));
	wrefresh(win);
}

static void	create_windows(t_vm *vm)
{
	int max_y;
	int max_x;
	int sub_height;
	int sub_width;

	max_y = 0;
	max_x = 0;

	getmaxyx(stdscr, max_y, max_x);
	sub_height = max_y / 3;
	sub_width = max_x - WIDTH;
	vm->visu->arena = newwin(HEIGHT, WIDTH, 1, 1);
	vm->visu->side1 = newwin(sub_height - 6, sub_width, 0, WIDTH);
	vm->visu->side2 = newwin(sub_height + 2, sub_width, sub_height - 7, WIDTH);
	vm->visu->side3 = newwin(sub_height + 4, sub_width, (sub_height * 2) - 6, WIDTH);
	vm->visu->side4 = newwin(5, sub_width, (sub_height * 3) - 3, WIDTH);
}

static void			init_visualizer(void)
{
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	curs_set(false);
	keypad(stdscr, true);
	nodelay(stdscr, true);
	define_colors();
}

void		start_visualizer(t_vm *vm)
{
	if (!(vm->visu = (t_visu*)malloc(sizeof(t_visu))))
		exit (1);
	init_visualizer();
	create_windows(vm);
	box_win(stdscr);
	set_owners(vm);
	draw_arena(vm);

	box_win(vm->visu->side1);
	box_win(vm->visu->side2);
	box_win(vm->visu->side3);
	box_win(vm->visu->side4);

	print_logo(vm->visu->side1);
	print_players(vm);
	battle_info(vm->visu->side3);
	signature(vm->visu->side4);
	print_player_info(vm);
	print_battle_info(vm, 10, 4);

	sleep (3);

	print_winner(vm);
	refresh();
	getchar();
    sleep (1);
    endwin();
}