/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visualizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:50:02 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/29 13:15:49 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	box_win(WINDOW *win)
{
	wattron(win, COLOR_PAIR(FRAME));
	box(win, 0, '*');
	wattroff(win, COLOR_PAIR(FRAME));
	wrefresh(win);
}

static void	create_windows(t_visu *visu)
{
	int max_y;
	int max_x;

	max_y = 0;
	max_x = 0;
	getmaxyx(stdscr, max_y, max_x);
	visu->arena = newwin(HEIGHT, WIDTH, 1, 1);
	visu->sidebar = newwin(max_y, max_x - WIDTH, 0, WIDTH);
}

static void			init_visualizer(void)
{
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
	t_visu	visu;

	init_visualizer();
	create_windows(&visu);
	box_win(stdscr);
	set_owners(vm, &visu);
	draw_arena(vm, &visu);
	box_win(visu.sidebar);

	getchar();
    sleep (1);
    endwin();
}
