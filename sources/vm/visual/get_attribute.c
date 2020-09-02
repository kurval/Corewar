/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 11:40:33 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/02 15:17:44 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

int			get_attribute(t_vm *vm, int idx)
{
	int owner;

	owner = vm->visu->attributes[idx].owner;
	if (vm->visu->attributes[idx].cursor == true)
		return (COLOR_PAIR(owner + 10));
	return (COLOR_PAIR(owner));
}