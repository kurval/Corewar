/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visualizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:50:02 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/10 16:08:17 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static int	get_speed(t_vm *vm, int key)
{
	if (key == KEY_LEFT && vm->visu->speed < 100000)
		vm->visu->speed += 10000;
	else if (key == KEY_RIGHT && vm->visu->speed > 10000)
		vm->visu->speed -= 10000;
	return (vm->visu->speed);
}

static void	exit_visu(t_vm *vm)
{
	free(vm->visu);
	free_proc_list(&vm->proc_list);
	endwin();
	ft_printf("Thanks for playing!\n");
	exit(1);
}

static void	pause_visu(t_vm *vm)
{
	int key;

	vm->visu->running = false;
	draw_logo(vm);
	while (!vm->visu->running)
	{
		key = getch();
		if (key == SPACE || key == 'd')
		{
			(key == 'd') ? vm->visu->debug = 0 : 0;
			vm->visu->running = true;
		}
		else if (key == ESC)
			exit_visu(vm);
	}
}

void		manage_windows(t_vm *vm, int key)
{
	draw_logo(vm);
	draw_arena(vm);
	draw_players(vm);
	draw_battle_info(vm);
	draw_footer(vm);
	if (key == ESC)
		exit_visu(vm);
	else if (key == 'd')
		vm->visu->debug = (!vm->visu->debug);
	if (key == SPACE || vm->visu->debug)
		pause_visu(vm);
	usleep(get_speed(vm, key));
}

void		start_visualizer(t_vm *vm)
{
	if (!(vm->visu = (t_visu*)malloc(sizeof(t_visu))))
		ft_errno(MALLOC_ERROR);
	init_visualizer(vm);
	run_cycles(vm);
	print_winner(vm);
	getchar();
	exit_visu(vm);
}
