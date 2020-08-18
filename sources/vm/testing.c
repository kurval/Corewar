/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:26:39 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/18 10:27:14 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void test(t_vm *vm)
{
	t_process *new;
	new = (t_process*)malloc(sizeof(t_process));
	new->next = NULL;
	new->opcode = 9;
	new->pc = 19;
	ft_printf("Valid? %d\n", get_args(vm, new));
	ft_printf("ARG1 %d\n", new->values[0]);
	ft_printf("ARG2 %d\n", new->values[1]);
	ft_printf("ARG3 %d\n", new->values[2]);
}
