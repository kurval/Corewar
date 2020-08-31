/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:15:31 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/31 10:16:05 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	load_code(unsigned char *arena, char *code, int len)
{
	int i;

	i = -1;
	while (++i < len)
	{
		arena[i] = code[i];
	}
}

void	load_oweners(int *owner, int id, int len)
{
	int i;

	i = -1;
	while (++i < len)
	{
		owner[i] = id;
	}
}

void	load_champions(t_vm *vm)
{
	int i;
	int location;
	int space;

	i = -1;
	location = 0;
	space = MEM_SIZE / vm->nb_players;
	while (vm->p[++i].id)
	{
		load_code(&(vm->a->arena[location]), &(vm->p[i].code[0]), vm->p[i].h.prog_size);
		load_oweners(&(vm->a->owner[location]), vm->p[i].id, vm->p[i].h.prog_size);
		location += space;
	}
	// print_arena(vm->a);
}
