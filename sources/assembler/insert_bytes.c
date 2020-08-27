/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:50:39 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/10 16:50:40 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	unsigned int	handle_negative(int number)
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
int state)
{
	unsigned char	*bytes;
	int				byte_nbr;

	bytes = get_bytes(fd, nbr, size);
	byte_nbr = write(fd, bytes, size);
	if (overlap(get_flags(), FLAG_X))
		write_hexdump(bytes, byte_nbr, state);
	free(bytes);
}

/*
**	Inserts a string (string) in a file (fd). If str length
**	is lower than size, the rest is padded with null bytes.
*/

void					insert_bytes_string(int fd, char *str, int size,
int state)
{
	int strlen;
	int	byte_nbr;

	strlen = ft_strlen(str);
	byte_nbr = write(fd, str, strlen);
	if (overlap(get_flags(), FLAG_X))
		write_hexdump((unsigned char *)str, byte_nbr, state);
	size = size - strlen;
	if (size > 0)
		insert_bytes_number(fd, 0, size, state);
}
