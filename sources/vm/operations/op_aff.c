/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:06 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/22 15:25:14 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Argument printed out as ASCII character.
*/

void	op_aff(t_vm *vm, t_process *proc)
{
	char val;

	val = (char)(get_op_values(vm, proc, 1) % 256);
	if (vm->a_flag)
		ft_printf("Aff: %c\n", val);
	if (vm->v_flag)
		(vm->visu->debug) ?\
		log_operation(vm, proc) : 0;
}
