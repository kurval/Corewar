/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 13:20:40 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/16 13:40:30 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	avl_flags(char *s, t_vm *vm)
{
	if ((ft_strequ("-a", s) && (vm->a_flag = 1))
		|| (ft_strequ("-v", s) && (vm->v_flag = 1))
		|| (ft_strequ("-l", s) && (vm->l_flag = 1)))
		return (1);
	return (0);
}

int	is_number_available(char **av, int num)
{
	int		i;
	char	number[2];

	i = 0;
	number[0] = num + 48;
	while (av[++i])
	{
		if (ft_strequ(av[i], &number[0]))
		{
			return (is_number_available(av, num + 1));
		}
	}
	if (num > MAX_PLAYERS)
		ft_errno(N_FLAG_ERROR);
	return (num);
}
