/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 13:20:40 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/17 17:03:01 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			avl_flags(char *s, t_vm *vm)
{
	if ((ft_strequ("-a", s) && (vm->a_flag = 1))
		|| (ft_strequ("-v", s) && (vm->v_flag = 1))
		|| (ft_strequ("-l", s) && (vm->l_flag = 1)))
		return (1);
	return (0);
}

static int	is_a_number(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int			is_number_available(char **av, int num)
{
	int		i;

	i = 0;
	while (av[++i])
	{
		if (is_a_number(av[i]) && (ft_atoi(av[i]) == num)
			&& ft_strequ("-n", av[i - 1]))
		{
			return (is_number_available(av, num + 1));
		}
	}
	if (num > MAX_PLAYERS)
		ft_errno(N_FLAG_ERROR);
	return (num);
}
