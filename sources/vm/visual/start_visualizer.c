/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visualizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:50:02 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/02 10:50:16 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	get_speed(t_vm *vm, int key)
{
	if (key == KEY_LEFT && vm->visu->speed < 100000)
		vm->visu->speed += 10000;
	else if (key == KEY_RIGHT && vm->visu->speed > 10000)
		vm->visu->speed -= 10000;
}

static void	pause_visu(t_vm *vm)
{
	vm->visu->running = 0;
	draw_logo(vm);
	while (!vm->visu->running)
	{
		if (getch() == 32)
			vm->visu->running = 1;
	}
}

static void	exit_visu(t_vm *vm)
{
	endwin();
	ft_printf("Thanks for playing!\n");
	free_all(vm);
}

void	manage_windows(t_vm *vm, int key)
{
	draw_logo(vm);
	draw_arena(vm);
	draw_players(vm);
	draw_battle_info(vm);
	draw_footer(vm);
	if (key == 27)
		exit_visu(vm);
	else if (vm->visu->running && key == 32)
		pause_visu(vm);
	get_speed(vm, key);
	usleep (vm->visu->speed);
}

void		start_visualizer(t_vm *vm)
{
	if (!(vm->visu = (t_visu*)malloc(sizeof(t_visu))))
		exit(1);
	init_visualizer(vm);
	run_cycles(vm);
	print_winner(vm);
	getchar();
    exit_visu(vm);
}
