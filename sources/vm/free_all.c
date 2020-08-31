/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 17:42:55 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/22 16:11:27 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	free_operations(t_vm *vm)
{
	free(vm->operations);
}

void		free_all(t_vm *vm)
{
	free_operations(vm);
	exit(1);
}
