/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 19:24:46 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/21 17:24:47 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void		print_info(t_vm *vm, t_player *player, int y, int x)
{
	WINDOW * win;
	win = vm->visu->side2;
	wattron(win, COLOR_PAIR(player->id) | A_BOLD);
	mvwprintw(win, y, x + 46, "%s", player->h.prog_name);
	wattroff(win, COLOR_PAIR(player->id) | A_BOLD);
	wattron(win, COLOR_PAIR(W_B) | A_BOLD);
	mvwprintw(win, y++, x + 40, "Name: ");
	mvwprintw(win, y++, x + 40, "Last live: %d", player->last_live);
	mvwprintw(win, y++, x + 40, "Period lives: %d", player->period_lives);
	wattroff(win, COLOR_PAIR(W_B) | A_BOLD);
}

void		print_player_info(t_vm *vm)
{
	unsigned int	i;
	int				x;
	int				y;

	i = -1;
	y = 3;
	x = 4;
	while (++i < vm->nb_players)
	{
		print_info(vm, &vm->p[i], y, x);
		y += 5;
	}
}
