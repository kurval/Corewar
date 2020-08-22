/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:35:39 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/22 11:14:24 by bkonjuha         ###   ########.fr       */
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

static void	get_player(char *s, t_player *p, int num[4])
{
	int fd;
	int len;
	int	i;

	i = 0;
	if ((fd = open(s, O_RDONLY)) != -1)
	{
		read(fd, &(p->h.magic), 4);
		read(fd, &(p->h.prog_name), PROG_NAME_LENGTH);
		lseek(fd, 8, SEEK_CUR);
		read(fd, &(p->h.comment), COMMENT_LENGTH);
		lseek(fd, 4, SEEK_CUR);
		len = read(fd, &(p->code), CHAMP_MAX_SIZE);
		while (!num[i])
			i++;
		p->id = num[i];
		p->h.prog_size = len;
	}
}

static int	get_n_flag(char *s, id[4])
{
	int num;

	if(ft_strlen(s) < 2 && ft_isdigit(*s))
		num = ft_atoi(s);
	if (num > 4 || num < 1)
		ft_errno(N_FLAG_ERROR);
	if (!id[num - 1])
		ft_errno(DUPLICATE_N);
	id[num - 1] = 0;
	return (num);
}

void		parse_input(char **av, t_vm *vm)
{
	int i;
	int	id[4];

	i = 0;
	id = {1, 2, 3, 4};
	while (av[++i])
	{
		if (ft_strequ("-n" , av[i++]))
			id = get_n_flag(av[i++])
		get_player(av[i], &(vm->p[i - 1]), id);
	}
	if (i > 4)
		ft_errno(CHAMP_NUM_ERROR);
	introduce_champs(vm);
}
