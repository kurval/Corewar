/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:52:15 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/12 18:28:22 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	*get_args(int instr_code, int argc)
{
	int			*args;
	static int	argv[16][3] = {{T_DIR, 0, 0}, {T_DIR | T_IND, T_REG, 0},
	{T_REG, T_IND | T_REG, 0}, {T_REG, T_REG, T_REG}, {T_REG, T_REG, T_REG},
	{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, {T_DIR, 0, 0},
	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, {T_DIR, 0, 0},
	{T_DIR | T_IND, T_REG, 0}, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	{T_DIR, 0, 0}, {T_REG, 0, 0}};

	if (!(args = (int *)malloc(sizeof(int) * argc)))
		exit(1);
	while (--argc >= 0)
		args[argc] = argv[instr_code][argc];
	return (args);
}

static t_op	get_instr(int instr_code)
{
	t_op		instr;
	static char	*instr_name[16] = {"live", "ld", "st", "add", "sub", "and",
	"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};
	static int	argc[16] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};
	static int	cycles[16] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, \
	50, 1000, 2};

	instr.instr_name = instr_name[instr_code];
	instr.argc = argc[instr_code];
	instr.argv = get_args(instr_code, argc[instr_code]);
	instr.wait_cycles = cycles[instr_code];
	instr.instr_code = instr_code;
	return (instr);
}

void		get_op(t_op *op)
{
	int		i;

	i = 16;
	while (--i >= 0)
		op[i] = get_instr(i);
}
