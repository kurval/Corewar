/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 16:55:01 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/22 16:32:35 by bkonjuha         ###   ########.fr       */
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

void    remove_proc(t_process **proc_list, t_process **current, t_process **previous)
{
    if (*previous)
        (*previous)->next = (*current)->next;
    else if (*proc_list == *current)
        *proc_list = (*current)->next;
    del_node(current);
    *current = (*previous) ? (*previous)->next : *proc_list;
}
