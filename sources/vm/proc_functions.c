/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 16:55:01 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/23 12:13:17 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Adding process start of the list
*/

void add_to_list(t_process *new, t_process **list)
{
	new->next = *list;
    *list = new;
}

t_process *new_proc()
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

void    remove_proc(t_vm *vm, t_process **proc_list, t_process **current, t_process **previous)
{
    vm->nb_procs--;
    if (*previous)
        (*previous)->next = (*current)->next;
    else if (*proc_list == *current)
        *proc_list = (*current)->next;
    del_node(current);
    *current = (*previous) ? (*previous)->next : *proc_list;
}

/*
** copies given process
** usen in fork and lfork operations
*/

t_process *copy_proc(t_vm *vm, t_process *og_proc)
{
    t_process   *new;
    int         i;

    new = new_proc();
    vm->nb_procs++;
    new->id = vm->id_counter++;
    new->carry = og_proc->carry;
    new->last_live = og_proc->last_live;
    new->jump = 0;
    new->wait_cycles = 0;
    i = -1;
	while (++i < REG_NUMBER)
        new->reg[i] = og_proc->reg[i];
    return (new);
}
