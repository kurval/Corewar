/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 15:52:01 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/31 19:35:32 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	decleare_winner(t_vm *vm)
{
	int win_nb;
	int i;

	win_nb = vm->last_live_id;
	i = -1;
	while (vm->p[++i].id)
	{
		if (vm->p[i].id == win_nb)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n", win_nb,
			vm->p[i].h.prog_name);
			return ;
		}
	}
}
