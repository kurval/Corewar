/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 07:53:44 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/28 11:25:40 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	get_dump(t_vm *vm, char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			ft_errno(DUMP_ERROR);
	if (vm->dump_cycle)
		ft_errno(DUMP_ERROR_SET);
	vm->dump_cycle = ft_atoi(s);
}
