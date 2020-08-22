/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:47:04 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/22 16:13:59 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void    init_arena(t_vm *vm, t_arena *arena)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        arena->arena[i] = 0;
        i++;
    }
    vm->a = arena;
}

void    print_arena(t_arena *arena)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        ft_printf("%.2X ", arena->arena[i]);
        i++;
        if (i % 64 == 0)
            ft_printf("\n");
    }
}

void    dump_memory(t_vm *vm)
{
    int i;

    i = 0;
    ft_printf("0x%#.4x : ", i);
    while (i < MEM_SIZE)
    {
        ft_printf("%.2X ", vm->a->arena[i]);
        i++;
        if (i % 32 == 0)
        {
            ft_printf("\n");
            i < MEM_SIZE ? ft_printf("%#.4x : ", i) : 0;
        }
    }
    free_all(vm);
}
