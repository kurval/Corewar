/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:01:39 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/12 14:01:40 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int		convert_dec(char *binary, int size)
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

char				*make_rev_binary_str(int nbr, int size)
{
	char	*binary;
	int		i;

	binary = ft_strnew(size);
	i = size - 1;
	while (i >= 0)
	{
		binary[i] = (nbr % 2 ? '0' : '1');
		i--;
		nbr = nbr / 2;
	}
	return (binary);
}
