/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_encoding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 11:32:29 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/13 13:49:42 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** This function compares encoding byte to
** operations table arguments of current
** operation code.
*/

static int check_op_args(t_vm *vm, int *args, int opcode)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if ((!(args[i] & vm->operations[opcode - 1].argv[i]) &&\
        args[i]) || (!args[i] && vm->operations[opcode - 1].argv[i]))
            return (0);
        i++;
    }
    return (1);
}

/*
** This function validates if encoding byte
** has valid argument types.
*/

static int check_types(int *args)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (args[i] == REG_CODE)
            args[i] = T_REG;
        else if (args[i] == DIR_CODE)
            args[i] = T_DIR;
        else if (args[i] == IND_CODE)
            args[i] = T_IND;
        else if (args[i] != 0)
            return (0);
        i++;
    }
    return (1);
}

int    validate_encoding(t_vm *vm, int encode_byte, int opcode)
{
    int arg[3];

    arg[0] = (encode_byte & MASK1) >> 6;
    arg[1] = (encode_byte & MASK2) >> 4;
    arg[2] = (encode_byte & MASK3) >> 2;

    return (check_types(arg) && check_op_args(vm, arg, opcode));
}