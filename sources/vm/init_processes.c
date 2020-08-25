/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 11:07:06 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/25 17:05:02 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Initializing process list.
*/

void    init_processes(t_vm *vm)
{
    unsigned int    i;
    int             j;
    t_process       *new;

    i = -1;
    j = 0;
    while(++i < vm->nb_players)
    {
        new = new_proc();
        vm->nb_procs++;
        new->id = vm->id_counter++;
        new->jump = 0;
        new->wait_cycles = 0;
        new->last_live = 0;
        new->carry = 0;
        new->pc = i * MEM_SIZE / vm->nb_players;
        new->player_id = vm->p[i].id;
        new->reg[0] = new->player_id * -1;
        while (++j < REG_NUMBER)
            new->reg[j] = 0;
        add_to_list(new, &vm->proc_list);
    }
    vm->last_live_id = vm->p[i-1].id;
}
