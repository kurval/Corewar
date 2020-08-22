/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:15:31 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/22 18:33:10 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	player_count(t_vm *vm)
{
	int i;

	i = 0;
	while (vm->p[i].id)
		i++;
	return (i);
}

void	load_champions(t_vm *vm)
{
	int i;
	int location;
	int space;

	i = -1;
	location = 0;
	space = MEM_SIZE / player_count(vm);
	while (vm->p[++i].id)
	{
		ft_memcpy(&(vm->a->arena[location]), &(vm->p[i].code), vm->p[i].h.prog_size);
		ft_memset(&(vm->a->owner[location]), vm->p[i].id, vm->p[i].h.prog_size);
		location += space;
	}
	print_arena(vm->a);
}
