/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cor_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:01:39 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/05 14:01:40 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		print_ascii(unsigned char *memory, int len)
{
	int i;

	i = 0;
	ft_printf(" \033[0;36m");
	while (i <= len)
	{
		if (memory[i] > 128)
			memory[i] = memory[i] - 128;
		ft_isprint(memory[i]) && memory[i] != ' ' ? \
		ft_printf("%c", memory[i]) : ft_printf("%c", '.');
		i++;
	}
	ft_printf("\033[0m\n");
}

static void		set_color_by_state(int state, unsigned char byte)
{
	if (state == magic)
		ft_printf("\033[1;36m");
	else if (state == name || state == comment)
	{
		if (byte)
			ft_printf("\033[1;34m");
		else
			ft_printf("\033[0;34m");
	}
	else if (state == exec)
		ft_printf("\033[0;35m");
	else if (state >= statement)
	{
		if (state % 2 == 0)
			ft_printf("\033[1;32m");
		else
			ft_printf("\033[1;33m");
	}
}

static void		write_offset(unsigned int hx_bytes)
{
	ft_printf("\033[1;37m");
	if (hx_bytes == 0)
		ft_printf("%49s %s\n",
		"0011 2233 4455 6677 8899 AABB CCDD EEFF",
		"0123456789ABCDEF");
	ft_printf("%08X: ", hx_bytes);
	ft_printf("\033[0m");
}

static void		finish_hexdump(unsigned int hx_bytes,
unsigned char *memory)
{
	ft_printf("%*s", 39 - ((hx_bytes % 16) * 2) - hx_bytes % 16 / 2, "");
	print_ascii(memory, hx_bytes % 16 - 1);
}

void			write_hexdump(unsigned char *bytes,
		int byte_nbr, t_state state)
{
	int						i;
	static unsigned int		hx_bytes = 0;
	static unsigned char	memory[16];

	i = 0;
	if (state == finish)
		return (finish_hexdump(hx_bytes, memory));
	while (i < byte_nbr)
	{
		if (hx_bytes % 16 == 0)
			write_offset(hx_bytes);
		set_color_by_state(state, bytes[i]);
		ft_printf("%.2x", bytes[i]);
		memory[hx_bytes % 16] = bytes[i];
		if ((hx_bytes + 1) % 16 == 0)
			print_ascii(memory, hx_bytes % 16);
		else if ((hx_bytes + 1) % 2 == 0)
			write(1, " ", 1);
		ft_printf("\033[0m");
		i++;
		hx_bytes = hx_bytes + 1;
	}
}
