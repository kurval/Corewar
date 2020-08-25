/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 07:53:44 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/25 08:08:25 by bkonjuha         ###   ########.fr       */
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
