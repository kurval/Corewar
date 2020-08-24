/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 11:45:06 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/14 21:04:26 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

/*
** Argument printed out as ASCII character.
*/

void	op_aff(t_vm *vm, t_process *proc)
{
	ft_putchar((char)get_op_values(vm, proc, 1));
}
