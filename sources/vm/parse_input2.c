/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 07:53:44 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/19 11:40:51 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	get_dump(t_vm *vm, char *s)
{
	int num;

	if (!ft_atoi_err(s))
		ft_errno(DUMP_ERROR, s);
	if (vm->dump)
		ft_errno(DUMP_ERROR_SET, s);
	vm->dump = true;
	if (ft_atoi(s) < 0)
		num = -1;
	else
		num = ft_atoi(s);
	vm->dump_cycle = num;
}

void	get_d_flag(t_vm *vm, char *s)
{
	int num;

	if (!ft_atoi_err(s))
		ft_errno(DUMP_ERROR, s);
	if (vm->dump)
		ft_errno(DUMP_ERROR_SET, s);
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
			ft_errno(MAGIC_ERROR, file);
	}
	else
		ft_errno(OPEN_ERROR, file);
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
			ft_errno(SPACE_ERROR, "Champion name, comment, \
			and exec code should be seperated by NULL bytes");
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
