/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:38 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/03 12:08:49 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

static void	set_live_on(t_vm *vm, t_process *proc, int i)
{
	vm->visu->attributes[proc->pc].owner = vm->p[i].id;
	vm->visu->attributes[proc->pc].live = LIVE_ON;
}

static void	print_live_text(t_vm *vm, t_process *proc)
{
	ft_printf("A process shows that player %d (%s) is alive\n",
	proc->player_id, vm->p[proc->player_id - 1].h.prog_name);
}

/*
** 1. Updates when cursor last reported alive.
** 2. If cursor's r1 == Argument1, set player as last reported alive.
** Remember r1 is initialised with the negated player id (r1 = -player_id).
*/

void		op_live(t_vm *vm, t_process *proc)
{
	int				value1;
	unsigned int	i;

	i = -1;
	vm->lives++;
	proc->last_live = vm->current_cycle;
	value1 = get_op_values(vm, proc, 1) * -1;
	while (++i < vm->nb_players)
	{
		if (vm->p[i].id == value1)
		{
			vm->p[i].last_live = vm->current_cycle;
			vm->p[i].period_lives++;
			vm->last_live_id = value1;
			if (vm->v_flag)
				set_live_on(vm, proc, i);
		}
	}
	if (vm->a_flag)
		print_live_text(vm, proc);
}
