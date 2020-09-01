/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:33:54 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/01 17:58:43 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	initialize_players(t_player *p)
{
	p->id = 0;
	p->h.magic = 0;
	p->h.prog_size = 0;
	p->last_live = 0;
	p->period_lives = 0;
	ft_bzero(&(p->code), CHAMP_MAX_SIZE);
	ft_bzero(&(p->h.comment), COMMENT_LENGTH);
	ft_bzero(&(p->h.prog_name), PROG_NAME_LENGTH);
}

void		init_vm(t_vm *vm)
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
	vm->operations = (t_op *)g_ops;
	while (++i < 4)
		initialize_players(&(vm->p[i]));
	vm->proc_list = NULL;
	vm->visu = NULL;
	vm->a_flag = 0;
    vm->v_flag = 0;
    vm->id_counter = 1;
}

/*
** Initializing process list.
*/

void		init_processes(t_vm *vm)
{
	unsigned int	i;
	int				j;
	t_process		*new;

	i = -1;
	j = 0;
	while (++i < vm->nb_players)
	{
		new = new_proc();
		vm->nb_procs++;
		new->id = vm->id_counter++;
		new->jump = 0;
		new->wait_cycles = 0;
		new->last_live = 0;
		new->carry = 0;
		new->pc = i * MEM_SIZE / vm->nb_players;
		new->player_id = vm->p[i].id;
		new->reg[0] = new->player_id * -1;
		while (++j < REG_NUMBER)
			new->reg[j] = 0;
		add_to_list(new, &vm->proc_list);
	}
	vm->last_live_id = vm->p[i - 1].id;
}

void		init_arena(t_vm *vm, t_arena *arena)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		arena->arena[i] = 0;
		arena->owner[i] = 0;
		i++;
	}
	vm->a = arena;
}
