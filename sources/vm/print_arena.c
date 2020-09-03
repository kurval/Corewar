/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:47:04 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/03 16:57:09 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_arena(t_arena *arena)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.2X ", arena->arena[i]);
		if (arena->owner[i] == 2)
			ft_printf("\033[0;31m");
		if (arena->owner[i] == 1)
			ft_printf("\033[0;32m");
		if (arena->owner[i] == 0)
			ft_printf("\033[0m");
		i++;
		if (i % 64 == 0)
			ft_printf("\n");
	}
}

void	free_proc_list(t_process **proc_list)
{
	t_process	*current;
	t_process	*next;

	current = *proc_list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*proc_list = NULL;
}

void	dump_memory(t_vm *vm)
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
	free_proc_list(&vm->proc_list);
	exit(1);
}
