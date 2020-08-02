/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:33:54 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/02 15:51:43 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/corewar_error.h"

t_vm	*init_vm(void)
{
	t_vm *vm;

	if (!(vm = (t_vm *)malloc(sizeof(t_vm))))
		ft_errno(VM_ERROR);
	vm->checks = 0;
	vm->current_cycle = 0;
	vm->cycles = 0;
	vm->last_live_id = 0;
	return (vm);
}
