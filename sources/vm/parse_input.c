/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:35:39 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/05 08:40:01 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	get_player(char *s, t_player p)
{
	int fd;

	if ((fd = open(s, O_RDONLY)) != -1)
	{
		read(fd, &(p.magic), 4);
		read(fd, &(p.prog_name), PROG_NAME_LENGTH);
		ft_printf("%s", &(p.prog_name));
	}
}

void		parse_input(char **av, t_vm *vm)
{
	int i;

	i = 0;
	while (av[++i])
		get_player(av[i], vm->p[i - 1]);
}
