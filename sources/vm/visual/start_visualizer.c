/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visualizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:50:02 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/14 15:12:51 by vkurkela         ###   ########.fr       */
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

	draw_logo(vm);
	while (true)
	{
		key = getch();
		if (key == SPACE || key == 'd')
		{
			if (key == 'd')
				set_debug(vm);
			vm->visu->running = true;
			return ;
		}
		else if (key == ESC)
			exit_visu(vm);
	}
}

void		manage_windows(t_vm *vm, int key)
{
	if (key == 'd')
	{
		vm->visu->log_count = -1;
		set_debug(vm);
	}
	else if (key == SPACE)
		vm->visu->running = false;
	else if (key == ESC)
		exit_visu(vm);
	draw_logo(vm);
	draw_arena(vm);
	(!vm->visu->debug) ? draw_players(vm) : 0;
	(vm->visu->debug) ? draw_log(vm) : 0;
	draw_battle_info(vm);
	draw_footer(vm);
	if (!vm->visu->running || vm->visu->debug)
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
