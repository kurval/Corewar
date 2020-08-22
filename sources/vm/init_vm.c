/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:33:54 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/22 18:54:25 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	initialize_players(t_player *p)
{
	p->id = 0;
	p->h.magic = 0;
	p->h.prog_size = 0;
	ft_bzero(&(p->code), CHAMP_MAX_SIZE);
	ft_bzero(&(p->h.comment), COMMENT_LENGTH);
	ft_bzero(&(p->h.prog_name), PROG_NAME_LENGTH);
}

void	init_vm(t_vm *vm)
{
	int i;

	i = -1;
	vm->checks = 0;
	vm->current_cycle = 0;
	vm->cycles = 0;
	vm->last_live_id = 0;
	vm->ctd = CYCLE_TO_DIE;
	vm->lives = 0;
	vm->dump_cycle = 0;
	vm->a = NULL;
	if (!(vm->operations = (t_op*)malloc(sizeof(t_op) * 16)))
		exit(1);
	while (++i < 4)
		initialize_players(&(vm->p[i]));
}
