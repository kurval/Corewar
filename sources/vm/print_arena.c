/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:47:04 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/10 16:08:25 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

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

void	print_arena(t_vm *vm)
{
	int i;

	i = 0;
	ft_printf("0x%#.4x : ", i);
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x ", vm->a->arena[i]);
		i++;
		if (i % 64 == 0)
		{
			ft_printf("\n");
			i < MEM_SIZE ? ft_printf("%#.4x : ", i) : 0;
		}
	}
	free_proc_list(&vm->proc_list);
	exit(1);
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
