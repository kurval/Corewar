/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:27:55 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/12 20:36:28 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		write_operation(int input_file, int output_file)
{
	int			ins;
	static char	*instr_name[16] = {"live", "ld", "st", "add", "sub", "and",
	"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};

	ins = 0;
	read(input_file, &ins, 1);
	if (ins)
		write(output_file, instr_name[ins - 1], ft_strlen(instr_name[ins - 1]));
	return (ins);
}

static char	*ft_itob(int num)
{
	char	*b;
	int		j;
	int		limit;

	limit = 128;
	j = 0;
	b = ft_strnew(8);
	ft_bzero(b, 8);
	while (limit)
	{
		if (num >= limit)
		{
			b[j] = '1';
			num %= limit;
		}
		else
			b[j] = '0';
		j++;
		limit /= 2;

	}
	return (b);
}

void	write_arguments(int input_file, int output_file, int ins)
{
	int	argc[16] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};
	unsigned char	arguments;
	char *binary;

	arguments = 0;
	if (ins == 1 || ins == 9 || ins == 12 || ins > 14)
		arguments = 128;
	else
		read(input_file, &arguments, 1);
	binary = ft_itob(arguments);
	while (argc[ins - 1]-- > 0)
	{
		if (ft_strnequ(binary, "01", 2))
			write_t_reg(output_file, input_file);
		else if (ft_strnequ(binary, "10", 2))
			write_t_dir(output_file, input_file, ins);
		else if (ft_strnequ(binary, "11", 2))
			write(output_file, "—", 1);
		argc[ins -1] != 0 ? write(output_file, ",", 1) : 0;
		binary += 2;
	}
}
