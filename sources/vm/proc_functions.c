/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 16:55:01 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/18 19:45:35 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void del_node(t_process **proc)
{
    free(*proc);
	*proc = NULL;
}

void    remove_proc(t_process **proc_list, t_process **current, t_process **previous)
{
    if (*previous && (*current)->next)
        (*previous)->next = (*current)->next;
    else
        *proc_list = (*current)->next;
    del_node(current);
    *current = (*previous) ? (*previous)->next : *proc_list;
}