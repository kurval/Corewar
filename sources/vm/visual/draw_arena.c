/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:15:26 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/21 16:04:00 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	draw_line(t_vm *vm, int i)
{
	unsigned int	j;
	int				attribute;

	j = -1;
	wprintw(vm->visu->arena, "  ");
	while (++j < MEM_SIZE / 64)
	{
		attribute = get_attribute(vm, i * 64 + j);
		waddch(vm->visu->arena, ' ');
		wattron(vm->visu->arena, attribute);
		wprintw(vm->visu->arena, "%.2x", vm->a->arena[i * 64 + j]);
		wattroff(vm->visu->arena, attribute);
		vm->visu->attributes[i * 64 + j].cursor = false;
	}
	wprintw(vm->visu->arena, " \n");
}

void		draw_arena(t_vm *vm)
{
	unsigned int	i;

	werase(vm->visu->arena);
	wprintw(vm->visu->arena, "\n\n");
	i = -1;
	while (++i < MEM_SIZE / 64)
		draw_line(vm, i);
	box_win(vm->visu->arena);
	wrefresh(vm->visu->arena);
}
