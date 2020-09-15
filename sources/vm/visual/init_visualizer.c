/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visualizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 17:25:01 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/15 21:20:20 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	set_owners(t_vm *vm)
{
	unsigned int i;
	unsigned int j;
	unsigned int addr;

	addr = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		vm->visu->attributes[i].owner = 0;
		vm->visu->attributes[i].live = 0;
		vm->visu->attributes[i].new_mem = 0;
	}
	i = -1;
	while (++i < vm->nb_players)
	{
		j = -1;
		while (++j < vm->p[i].h.prog_size)
		{
			(j == 0) ? vm->visu->attributes[addr].cursor = true : 0;
			vm->visu->attributes[addr + j].owner = vm->p[i].id;
		}
		addr += MEM_SIZE / vm->nb_players;
	}
}

void		box_win(WINDOW *win)
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
	vm->visu->arena = newwin(HEIGHT, WIDTH, 0, 0);
	vm->visu->side1 = newwin(sub_height - 6, sub_width, 0, WIDTH);
	vm->visu->side2 = newwin(sub_height + 2, sub_width, sub_height - 7, WIDTH);
	vm->visu->side3 = newwin(sub_height + 4, sub_width,\
	(sub_height * 2) - 6, WIDTH);
	vm->visu->side4 = newwin(5, sub_width, (sub_height * 3) - 3, WIDTH);
}

void		init_visualizer(t_vm *vm)
{
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	curs_set(false);
	keypad(stdscr, true);
	nodelay(stdscr, true);
	define_colors();
	create_windows(vm);
	set_owners(vm);
	vm->visu->speed = 20100;
	vm->visu->running = false;
	vm->visu->debug = false;
	vm->visu->log_count = 0;
	vm->visu->end = false;
}
