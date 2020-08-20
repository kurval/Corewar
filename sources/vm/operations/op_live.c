/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:38 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/20 15:38:31 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** 1. Updates when cursor last reported alive.
** 2. If cursor's r1 == Argument1, set player as last reported alive.
** Remember r1 is initialised with the negated player id (r1 = -player_id).
*/

void	op_live(t_vm *vm, t_process *proc)
{
	/*
	//For testing purposes.
	t_player	player;

	player.id = 0;
	player.name = "Name";
	proc->player = &player;
	*/
	int value1;

	vm->lives++;
	proc->last_live = vm->current_cycle;
	value1 = get_op_values(vm, proc, 1);
	if (proc->reg[0] == value1 * -1)
		vm->last_live_id = value1;
	ft_printf("A process shows that player %d (%s) is alive\n",
	((t_player *)proc->player)->id, ((t_player *)proc->player)->name);
}
