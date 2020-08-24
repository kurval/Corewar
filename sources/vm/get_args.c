/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:48:48 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/24 15:41:10 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Returns short from unsigned char.
** 2 bytes
*/

static short	short_arg(t_vm *vm, int idx)
{
    short res;

    res = vm->a->arena[get_addr(idx)] * 256;
    res += vm->a->arena[get_addr(idx + 1)];
	return (res);
}

/*
** Returns int from unsigned char.
** 4 bytes
*/

int		int_arg(t_vm *vm, int idx)
{
	int		res;
	int		i;

	res = vm->a->arena[get_addr(idx)];
	i = 0;
	while (++i < 4)
		res = res * 256 + vm->a->arena[get_addr(idx + i)];
	return (res);
}

/*
** Getting values depending type and labels
** and also validate registry numbers if present
*/

static int  get_values(t_vm *vm, t_process *proc, int arg_num)
{
    int ret;

    ret = 1;
    if (proc->args[arg_num] == T_REG)
    {
        proc->values[arg_num] = vm->a->arena[get_addr(proc->pc + proc->jump)];
        if (proc->values[arg_num] < 1 ||  proc->values[arg_num] > REG_NUMBER)
            ret = 0;
    }
    else if (proc->args[arg_num] == T_DIR && vm->operations[proc->opcode - 1].dir_size == 4)
        proc->values[arg_num] = int_arg(vm, proc->pc + proc->jump);
    else if (proc->args[arg_num] == T_IND || proc->args[arg_num] == T_DIR)
        proc->values[arg_num] = short_arg(vm, proc->pc + proc->jump);
    return (ret);
}

/*
** To get to the next operation, cursor must skip operation byte,
** encoding byte (if present), and arguments saved in the encoding byte.
*/

static int  count_moves(t_vm *vm, t_process *proc)
{
    int i;
    int valid;

    i = -1;
    valid = 1;
    proc->jump = 1;
    proc->jump += (vm->operations[proc->opcode - 1].encode) ? 1 : 0;
    while (++i < vm->operations[proc->opcode - 1].argc && valid)
    {
        valid = get_values(vm, proc, i);
        (proc->args[i] == T_REG) ? proc->jump +=  1 : 0;
        (proc->args[i] == T_DIR) ? proc->jump += \
        vm->operations[proc->opcode - 1].dir_size : 0;
        (proc->args[i] == T_IND) ? proc->jump +=  2 : 0;
    }
    return valid;
}

/*
** This function checks that arguments are valid
** and saves values of current cursor's arguments.
** Also counts the steps to move to next operation.
*/

int    get_args(t_vm *vm, t_process *proc)
{
    int valid;

    valid = 1;
    if (vm->operations[proc->opcode - 1].encode)
        valid = validate_encoding(vm, vm->a->arena[get_addr(proc->pc + 1)], proc);
    else
        proc->args[0] = T_DIR;
    return (valid && count_moves(vm, proc));
}