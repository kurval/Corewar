/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 23:25:59 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/02 10:51:34 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Sests value from registry into the arena as unsigned char.
*/

void	load_into_memory(t_vm *vm, unsigned int addr,\
		void *content, t_process *proc)
{
	int	i;

	i = -1;
	while (++i < REG_SIZE)
	{
		vm->a->arena[get_addr(addr + i)] =\
		((unsigned char *)content)[REG_SIZE - i - 1];
		if (vm->v_flag)
			vm->visu->attributes[get_addr(addr + i)].owner =\
			proc->player_id;
	}
}

/*
** This function returns value depending on type:
** If type is T_REG it return value from registry number
** If type is T_IND it return value from position + T_IND
** If type is T_DIR it return number from T_DIR argument
*/

int		get_op_values(t_vm *vm, t_process *proc, int arg)
{
	int value;
	int type;

	value = proc->values[arg - 1];
	type = proc->args[arg - 1];
	if (type == T_REG)
		return (proc->reg[value - 1]);
	else if (type == T_IND)
		return (int_arg(vm, proc->pc + value % IDX_MOD));
	else if (type == T_DIR)
		return (value);
	return (0);
}
