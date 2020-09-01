/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visualizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:50:02 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/01 06:44:25 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	manage_windows(t_vm *vm)
{
	draw_arena(vm);
	draw_players(vm);
	draw_battle_info(vm);
}

void		start_visualizer(t_vm *vm)
{
	if (!(vm->visu = (t_visu*)malloc(sizeof(t_visu))))
		exit(1);
	init_visualizer(vm);
	manage_windows(vm);
	sleep (3);
	print_winner(vm);
	getchar();
    sleep (1);
    endwin();
}
