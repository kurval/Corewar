/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:15:26 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/29 13:17:13 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void	draw_arena(t_vm *vm, t_visu	*visu)
{
	unsigned int i;
	unsigned int j;
	int attribute;

	werase(visu->arena);
	wprintw(visu->arena, "\n");
	i = -1;
	while (++i < MEM_SIZE / 64)
	{
		j = -1;
		wprintw(visu->arena, " ");
		while (++j < MEM_SIZE / 64)
		{
			attribute = get_attribute(visu, i * 64 + j);
			waddch(visu->arena, ' ');
			wattron(visu->arena, attribute);
			wprintw(visu->arena, "%.2x", vm->a->arena[i * 64 + j]);
			wattroff(visu->arena, attribute);
		}
		wprintw(visu->arena, " \n");
	}
	wrefresh(visu->arena);
}

void	set_owners(t_vm *vm, t_visu	*visu)
{
	unsigned int i;
	unsigned int j;
	unsigned int addr;

	addr = 0;
	i = -1;
	while (++i < MEM_SIZE)
		visu->attr_arena[i].owner = 0;
	i = -1;
	while (++i < vm->nb_players)
	{
		j = -1;
		while (++j < vm->p[i].h.prog_size)
			visu->attr_arena[addr + j].owner = vm->p[i].id;
		addr += MEM_SIZE / vm->nb_players;
	}
}
