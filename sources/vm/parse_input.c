/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:35:39 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/30 11:11:08 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	introduce_champs(t_vm *vm)
{
	int i;
	int	num;

	i = -1;
	num = 0;
	ft_putendl("Introducing contestants...");
	while (++i < 4)
	{
		if (vm->p[i].id)
		{
			ft_printf("* Player %d, Weighing in at %d BYTES, \"%s\": (\"%s\")\n",
				i + 1, vm->p[i].h.prog_size, vm->p[i].h.prog_name, vm->p[i].h.comment);
			num++;
		}
	}
	vm->nb_players = num;
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
		close(fd);
	}
}

static int	get_n_flag(char *s, int id[4])
{
	int num;

	if (!(ft_strlen(s) < 2) || !(ft_isdigit(*s)))
		ft_errno(N_FLAG_ERROR);
	num = ft_atoi(s);
	if (num > MAX_PLAYERS || num < 1)
		ft_errno(N_FLAG_ERROR);
	if (!id[num - 1])
		ft_errno(DUPLICATE_N);
	id[num - 1] = 0;
	return (num);
}

static int			get_next_unused_id(int arr[MAX_PLAYERS])
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS && !arr[i])
		i++;
	if (i == MAX_PLAYERS)
		ft_errno(CHAMP_NUM_ERROR);
	arr[i] = 0;
	return (i + 1);
}

void		parse_input(int ac, char **av, t_vm *vm)
{
	int i;
	int	id_arr[MAX_PLAYERS];
	int	num;

	i = 0;
	id_arr[0] = 1;
	id_arr[1] = 2;
	id_arr[2] = 3;
	id_arr[3] = 4;
	while (av[++i])
	{
		num = 0;
		if (ft_strequ("-n" , av[i]) && i < ac && i++)
			num = get_n_flag(av[i++], id_arr);
		else if (ft_strequ("-dump" , av[i]) && i < ac && i++)
			get_dump(vm, av[i++]);
		else if (ft_strequ("-a", av[i]) && (vm->a_flag = 1))
			vm->a_flag = 1;
		else
			num = get_next_unused_id(id_arr);
		get_player(av[i], &(vm->p[num - 1]), num);
	}
	introduce_champs(vm);
}
