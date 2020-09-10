/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 07:53:44 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/11 01:06:01 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		get_dump(t_vm *vm, char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			ft_errno(DUMP_ERROR);
	if (vm->dump_cycle)
		ft_errno(DUMP_ERROR_SET);
	return (ft_atoi(s));
}

void	has_magic_header(char *file)
{
	unsigned char	magic[4];
	int				fd;

	if ((fd = open(file, O_RDONLY)) > 0)
	{
		read(fd, &magic[3], 1);
		read(fd, &magic[2], 1);
		read(fd, &magic[1], 1);
		read(fd, &magic[0], 1);
		if (*(unsigned int *)magic != COREWAR_EXEC_MAGIC)
			ft_errno(MAGIC_ERROR);
	}
	else
		ft_errno(OPEN_ERROR);
}

int		check_flags(char **av, int *i, int id_arr[4], t_vm *vm)
{
	int num;

	num = 0;
	if (ft_strequ("-n", av[*i]) && *i++)
		num = get_n_flag(av[*i += 1], id_arr, vm->nb_players);
	else
		num = get_next_unused_id(id_arr);
	if (ft_strequ("-dump", av[*i]) && *i++)
		vm->dump_cycle = get_dump(vm, av[*i++]);
	if (ft_strequ("-d", av[*i]) && *i++)
		vm->d_flag = get_dump(vm, av[*i += 1]);
	else if ((ft_strequ("-a", av[*i]) && (vm->a_flag = 1))
			|| (ft_strequ("-v", av[*i]) && (vm->v_flag = 1)))
		*i += 1;
	return (num);
}
