/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:22:12 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/14 08:20:01 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		read_n_bytes(int input, int count)
{
	unsigned char	number;
	int				result;

	number = 0;
	result = 0;
	while (count--)
	{
		result = result << 8;
		read(input, &number, 1);
		result += number;
	}
	return (result);
}

void	write_t_reg(int output, int input)
{
	char number;

	number = 0;
	write(output, " r", 2);
	number = read_n_bytes(input, 1);
	ft_putnbr_fd(number, output);
}

void	write_t_dir(int output, int input, int ins)
{
	int		number;
	short	s_num;

	write(output, " %", 2);
	number = 0;
	s_num = 0;
	if (ins > 8 && ins < 17 && ins != 13)
	{
		s_num = read_n_bytes(input, 2);
		ft_putnbr_fd(s_num, output);
	}
	else
	{
		number = read_n_bytes(input, 4);
		ft_putnbr_fd(number, output);
	}
}

void	write_t_ind(int output, int input)
{
	short number;

	number = 0;
	number = read_n_bytes(input, 2);
	ft_putnbr_fd(number, output);
}
