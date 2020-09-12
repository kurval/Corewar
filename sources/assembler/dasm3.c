/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:22:12 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/12 20:55:25 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_t_reg(int output, int input)
{
	unsigned char number;

	write(output, " r", 2);
	read(input, &number, 1);
	number += 48;
	write(output, &(number), 1);
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
		result = result<<8;
		read(input, &number, 1);
		result += number;
	}
	return (result);
}

void	write_t_dir(int output, int input, int ins)
{
	int number;

	write(output, " %", 2);
	number = 0;
	if (ins > 8 && ins < 17 && ins != 13)
		number = read_n_bytes(input, 2);
	else
		number = read_n_bytes(input, 4);
	ft_putnbr_fd(number, output);
}

void	write_t_ind(int output, int input)
{
	int number;

	number = read_n_bytes(input, 2);
	ft_putnbr_fd(number, output);
}
