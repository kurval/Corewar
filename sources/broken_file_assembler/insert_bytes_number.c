/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_bytes_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:50:39 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/10 16:50:40 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int			convert_dec(char *binary, int size)
{
	int				multiplier;
	int				i;
	unsigned int	result;

	multiplier = 1;
	i = size - 1;
	result = 0;
	while (i >= 0)
	{
		if (binary[i] == '1')
			result = result + multiplier;
		i--;
		multiplier = multiplier * 2;
	}
	ft_strdel(&binary);
	return (result);
}

static char				*make_rev_binary_str(int nbr, int size)
{
	char	*binary;
	int		i;

	if (!(binary = ft_strnew(size)))
		handle_error(MALLOC_ERROR);
	i = size - 1;
	while (i >= 0)
	{
		binary[i] = (nbr % 2 ? '0' : '1');
		i--;
		nbr = nbr / 2;
	}
	return (binary);
}

static unsigned int		handle_negative(int number)
{
	char			*binary;
	unsigned int	result;

	binary = make_rev_binary_str(number, 32);
	result = convert_dec(binary, 32);
	return (result + 1);
}

static unsigned char	*get_bytes(int fd, int number, int byte_nbr)
{
	int				byte;
	unsigned char	*output;
	int				i;
	unsigned int	uint_number;

	if (number < 0)
		uint_number = handle_negative(number);
	else
		uint_number = (unsigned int)number;
	if (!(output = (unsigned char *)malloc(sizeof(unsigned char) * byte_nbr)))
		handle_error(MALLOC_ERROR);
	i = byte_nbr - 1;
	byte = 1;
	while ((byte && i > -1) || i > -1)
	{
		byte = (uint_number & 0xFF);
		output[i] = (unsigned char)byte;
		uint_number = (uint_number >> 8);
		i--;
	}
	return (output);
}

/*
**	Inserts a number (nbr) in a file(fd). THe number is written
**	in bytes in big endian style.
*/

void					insert_bytes_number(int fd, int nbr, int size,
t_state state)
{
	unsigned char	*bytes;
	int				byte_nbr;

	bytes = get_bytes(fd, nbr, size);
	byte_nbr = write(fd, bytes, size);
	if (overlap(g_flags, flag_x))
		write_hexdump(bytes, byte_nbr, state);
	free(bytes);
}
