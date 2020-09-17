/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:27:55 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/17 17:18:07 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

static int	*get_argc(void)
{
	int *argc;

	if (!(argc = (int *)malloc(sizeof(int) * 16)))
		handle_error("Error: Could not allocate variable");
	argc[0] = 1;
	argc[1] = 2;
	argc[2] = 2;
	argc[3] = 3;
	argc[4] = 3;
	argc[5] = 3;
	argc[6] = 3;
	argc[7] = 3;
	argc[8] = 1;
	argc[9] = 3;
	argc[10] = 3;
	argc[11] = 1;
	argc[12] = 2;
	argc[13] = 3;
	argc[14] = 1;
	argc[15] = 1;
	return (argc);
}

void		write_arguments(int input, int output, int ins)
{
	int				*argc;
	int				i;
	unsigned char	arguments;
	char			*binary;

	arguments = 0;
	i = 0;
	argc = get_argc();
	if (ins == 1 || ins == 9 || ins == 12 || ins == 15)
		arguments = 128;
	else
		read(input, &arguments, 1);
	binary = ft_itob(arguments);
	while (argc[ins - 1]-- > 0)
	{
		ft_strnequ(binary + i, "01", 2) ? write_t_reg(output, input) : 0;
		ft_strnequ(binary + i, "10", 2) ? write_t_dir(output, input, ins) : 0;
		ft_strnequ(binary + i, "11", 2) ? write_t_ind(output, input) : 0;
		argc[ins - 1] != 0 ? write(output, ",", 1) : 0;
		i += 2;
	}
	free((void *)argc);
	ft_strdel(&binary);
}

int			write_operation(int input_file, int output_file)
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
