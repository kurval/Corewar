/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 19:24:46 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/30 20:09:43 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void print_info(t_vm *vm, t_player *player, int y, int x)
{
    wattron(vm->visu->side2, COLOR_PAIR(player->id) | A_BOLD);
    mvwprintw(vm->visu->side2, y + 1, x + 46, "%s", player->h.prog_name);
    wattron(vm->visu->side2, COLOR_PAIR(W_B) | A_BOLD);
    mvwprintw(vm->visu->side2, y + 1, x + 40, "Name: ");
    mvwprintw(vm->visu->side2, y + 2, x + 40, "Lives: %d", 0);
    mvwprintw(vm->visu->side2, y + 3, x + 40, "Period lives: %d", 0);
    wattroff(vm->visu->side2, COLOR_PAIR(W_B) | A_BOLD);
}

void    print_player_info(t_vm *vm)
{
    int i;
    int x;
    int y;

	i = -1;
    y = 2;
    x = 4;
	while (vm->p[++i].id)
    {
        print_info(vm, &vm->p[i], y, x);
        y += 5;
    }
    wrefresh(vm->visu->side2);
}