/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:15:26 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/30 18:59:35 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void	draw_arena(t_vm *vm)
{
	unsigned int i;
	unsigned int j;
	int attribute;

	werase(vm->visu->arena);
	wprintw(vm->visu->arena, "\n");
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
	wrefresh(vm->visu->arena);
}

void	set_owners(t_vm *vm)
{
	unsigned int i;
	unsigned int j;
	unsigned int addr;

	addr = 0;
	i = -1;
	while (++i < MEM_SIZE)
		vm->visu->attr_arena[i].owner = 0;
	i = -1;
	while (++i < vm->nb_players)
	{
		j = -1;
		while (++j < vm->p[i].h.prog_size)
			vm->visu->attr_arena[addr + j].owner = vm->p[i].id;
		addr += MEM_SIZE / vm->nb_players;
	}
}
