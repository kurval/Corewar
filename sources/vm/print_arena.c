/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:47:04 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/08 12:33:55 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
#include "../../libft/libft.h"

void    init_arena(t_arena *arena)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        arena->arena[i] = 0;
        i++;
    }
}

void    print_arena(t_arena *arena)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        ft_printf("%3X", arena->arena[i]);
        i++;
        if (i % 64 == 0)
            ft_printf("\n");
    }
}