/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:35:39 by bkonjuha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/08/21 12:23:55 by vkurkela         ###   ########.fr       */
=======
/*   Updated: 2020/08/16 14:14:43 by bkonjuha         ###   ########.fr       */
>>>>>>> Parse Champions and allocate to arena
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	introduce_champs(t_vm *vm)
{
	int i;

	i = -1;
	ft_putendl("Introducing contestants...");
	while (vm->p[++i].id)
	{
		ft_printf("* Player %d, Weighing in at %d BYTES, \"%s\": (\"%s\")\n",
			i + 1, vm->p[i].h.prog_size, vm->p[i].h.prog_name, vm->p[i].h.comment);
	}

}

static void	get_player(char *s, t_player *p, int num)
{
	int fd;
	int len;

	if ((fd = open(s, O_RDONLY)) != -1)
	{
		read(fd, &(p->h.magic), 4);
		read(fd, &(p->h.prog_name), PROG_NAME_LENGTH);
		lseek(fd, 8, SEEK_CUR);
		read(fd, &(p->h.comment), COMMENT_LENGTH);
		lseek(fd, 4, SEEK_CUR);
		len = read(fd, &(p->code), CHAMP_MAX_SIZE);
		p->id = num;
		p->h.prog_size = len;
	}
}

void		parse_input(char **av, t_vm *vm)
{
	int i;

	i = 0;
	while (av[++i])
		get_player(av[i], &(vm->p[i - 1]), i);
	if (i > 4)
		ft_errno(CHAMP_NUM_ERROR);
	introduce_champs(vm);
}
