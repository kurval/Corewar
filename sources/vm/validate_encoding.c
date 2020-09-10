/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_encoding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 11:32:29 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/10 23:14:48 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** This function compares encoding byte to
** operations table arguments of current
** operation code.
*/

static int	check_op_args(t_vm *vm, int *args, t_process *proc)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if ((!(args[i] & vm->operations[proc->opcode - 1].argv[i]) &&\
		args[i]) || (!args[i] && vm->operations[proc->opcode - 1].argv[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** This function validates if encoding byte
** has valid argument types and also saves
** types for current cursor.
*/

static void	get_types(t_vm *vm, int *args, t_process *proc)
{
	int i;

	i = 0;
	while (i < vm->operations[proc->opcode - 1].argc)
	{
		if (args[i] == REG_CODE)
			proc->args[i] = T_REG;
		else if (args[i] == DIR_CODE)
			proc->args[i] = T_DIR;
		else if (args[i] == IND_CODE)
			proc->args[i] = T_IND;
		else
			proc->args[i] = 0;
		i++;
	}
}

int			validate_encoding(t_vm *vm, int encode_byte, t_process *proc)
{
	int arg[3];
	int	i;

	i = -1;
	while (++i < 3)
		proc->args[i] = 0;
	arg[0] = (encode_byte & MASK1) >> 6;
	arg[1] = (encode_byte & MASK2) >> 4;
	arg[2] = (encode_byte & MASK3) >> 2;
	get_types(vm, arg, proc);
	return (check_op_args(vm, proc->args, proc));
}
