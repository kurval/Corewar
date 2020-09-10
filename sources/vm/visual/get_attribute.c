/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 11:40:33 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/10 15:59:56 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

int			get_attribute(t_vm *vm, int addr)
{
	int owner;

	owner = vm->visu->attributes[addr].owner;
	if (vm->visu->attributes[addr].live-- > 0)
		return (COLOR_PAIR(owner + 20));
	else if (vm->visu->attributes[addr].cursor == true)
		return (COLOR_PAIR(owner + 10));
	else if (vm->visu->attributes[addr].new_mem-- > 0)
		return (COLOR_PAIR(owner) | A_BOLD);
	return (COLOR_PAIR(owner));
}
