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

static char	*get_bytes(int fd, int number, int byte_nbr)
{
	int		byte;
	char	*output;
	int		i;

	output = (char *)malloc(sizeof(char) * byte_nbr);
	i = byte_nbr - 1;
	while (byte || i > -1)
	{
		byte = (number & 0xFF);
		output[i] = (char)byte;
		number = (number >> 8);
		i--;
	}
	return (output);
}

/*
**	Inserts a number (nbr) in a file(fd). THe number is written
**	in bytes in big endian style.
*/

void		insert_bytes_number(int fd, int nbr, int size)
{
	char *bytes;

	bytes = get_bytes(fd, nbr, size);
	write(fd, bytes, size);
	free(bytes);
}

/*
**	Inserts a string (string) in a file (fd). If str length
**	is lower than size, the rest is padded with null bytes.
*/

void		insert_bytes_string(int fd, char *str, int size)
{
	int strlen;

	strlen = ft_strlen(str);
	write(fd, str, strlen);
	size = size - strlen;
	if (size > 0)
		insert_bytes_number(fd, 0, size);
}
