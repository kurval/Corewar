/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 07:53:44 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/16 20:07:27 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
**	TODO: Merge get_dump and get_d_flag into one function;
*/

void	get_dump(t_vm *vm, char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			ft_errno(DUMP_ERROR);
	if (vm->dump)
		ft_errno(DUMP_ERROR_SET);
	vm->dump = true;
	vm->dump_cycle = ft_atoi(s);
}

void	get_d_flag(t_vm *vm, char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			ft_errno(DUMP_ERROR);
	if (vm->dump)
		ft_errno(DUMP_ERROR_SET);
	vm->dump = true;
	vm->d_flag = ft_atoi(s);
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

void	has_white_space(int fd)
{
	unsigned char	character;
	int				i;

	i = 0;
	while (i < 4)
	{
		read(fd, &character, 1);
		if (character)
			ft_errno(SPACE_ERROR);
		i++;
	}
}

int		read_n_bytes(int input, int count)
{
	unsigned char	number;
	int				result;
	int				i;

	i = 0;
	number = 0;
	result = 0;
	while (i++ < count)
	{
		result = result << 8;
		read(input, &number, 1);
		result += number;
	}
	return (result);
}
