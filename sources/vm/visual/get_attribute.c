/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 11:40:33 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/30 18:57:05 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static int	normal_color(int owner)
{
	if (owner == 1)
		return (COLOR_PAIR(GREEN));
	if (owner == 2)
		return (COLOR_PAIR(B_B));
	if (owner == 3)
		return (COLOR_PAIR(Y_B));
	if (owner == 4)
		return (COLOR_PAIR(R_B));
	return (COLOR_PAIR(G_B));
}

int			get_attribute(t_vm *vm, int idx)
{
	return (normal_color(vm->visu->attr_arena[idx].owner));
}