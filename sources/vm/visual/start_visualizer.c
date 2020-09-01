/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visualizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:50:02 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/01 09:22:25 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void	manage_windows(t_vm *vm)
{
	draw_arena(vm);
	draw_players(vm);
	draw_battle_info(vm);
	usleep (1000);
}

void		start_visualizer(t_vm *vm)
{
	if (!(vm->visu = (t_visu*)malloc(sizeof(t_visu))))
		exit(1);
	init_visualizer(vm);
	manage_windows(vm);
	run_cycles(vm);
	print_winner(vm);
	getchar();
    sleep (1);
    endwin();
	free_all(vm);
}
