/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 07:53:44 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/17 11:37:32 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	get_dump(t_vm *vm, char *s)
{
	int i;
	int num;

	i = -1;
	if (!ft_atoi_err(s))
		ft_errno(DUMP_ERROR);
	if (vm->dump)
		ft_errno(DUMP_ERROR_SET);
	vm->dump = true;
	if (ft_atoi(s) < 0)
		num = -1;
	else
		num = ft_atoi(s);
	vm->dump_cycle = num;
}

void	get_d_flag(t_vm *vm, char *s)
{
	int i;
	int num;

	i = -1;
	if (!ft_atoi_err(s))
		ft_errno(DUMP_ERROR);
	if (vm->dump)
		ft_errno(DUMP_ERROR_SET);
	vm->dump = true;
	if (ft_atoi(s) < 0)
		num = -1;
	else
		num = ft_atoi(s);
	vm->d_flag = num;
}

void	has_magic_header(char *file)
{
	unsigned int	magic;
	int				fd;

	if ((fd = open(file, O_RDONLY)) > 0)
	{
		magic = read_n_bytes(fd, 4);
		if (magic != COREWAR_EXEC_MAGIC)
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
