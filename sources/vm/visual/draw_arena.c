/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:15:26 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/01 06:37:35 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void	draw_arena(t_vm *vm)
{
	unsigned int i;
	unsigned int j;
	int attribute;

	werase(vm->visu->arena);
	wprintw(vm->visu->arena, "\n\n");
	i = -1;
	while (++i < MEM_SIZE / 64)
	{
		j = -1;
		wprintw(vm->visu->arena, " ");
		while (++j < MEM_SIZE / 64)
		{
			attribute = get_attribute(vm, i * 64 + j);
			waddch(vm->visu->arena, ' ');
			wattron(vm->visu->arena, attribute);
			wprintw(vm->visu->arena, "%.2x", vm->a->arena[i * 64 + j]);
			wattroff(vm->visu->arena, attribute);
		}
		wprintw(vm->visu->arena, " \n");
	}
	box_win(vm->visu->arena);
	wrefresh(vm->visu->arena);
}
