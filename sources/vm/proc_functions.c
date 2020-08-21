/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 16:55:01 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/21 23:00:58 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void add_to_list(t_process *new, t_process **list)
{
	new->next = *list;
    *list = new;
}

static t_process *new_proc()
{
    t_process *new;

    if (!(new = (t_process*)malloc(sizeof(t_process))))
        exit(1);
    new->next = NULL;
    return new;
}

static void del_node(t_process **proc)
{
    free(*proc);
	*proc = NULL;
}

/*
** Check if node is not the first on the list:
** >point prev to current->next
** If node is the first on the list:
** >point the head to current->next
*/

void    remove_proc(t_process **proc_list, t_process **current, t_process **previous)
{
    if (*previous)
        (*previous)->next = (*current)->next;
    else if (*proc_list == *current)
        *proc_list = (*current)->next;
    del_node(current);
    *current = (*previous) ? (*previous)->next : *proc_list;
}

/*
** Initializing process list.
*/

void    init_processes(t_vm *vm)
{
    int i;
    int player_nb;
    t_process *new;

    i = -1;
    while(++i < vm->nb_players)
    {
        new = new_proc();
        new->id = i + 1;
        new->jump = 0;
        new->wait_cycles = 0;
        new->last_live = 0;
        new->carry = 0;
        new->pc = i * MEM_SIZE / vm->nb_players;
        player_nb = -1 * vm->p[i].id;
        new->reg[0] = player_nb;
        add_to_list(new, &vm->proc_list);
    }
}