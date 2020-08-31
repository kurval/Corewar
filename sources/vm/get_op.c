/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:52:15 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/28 11:07:59 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		*assign_opfunctions(int opcode)
{
	void	(*f)(t_vm *vm, t_process *proc);

	opcode == 1 ? f = op_live : 0;
	opcode == 2 ? f = op_ld : 0;
	opcode == 3 ? f = op_st : 0;
	opcode == 4 ? f = op_add : 0;
	opcode == 5 ? f = op_sub : 0;
	opcode == 6 ? f = op_and : 0;
	opcode == 7 ? f = op_or : 0;
	opcode == 8 ? f = op_xor : 0;
	opcode == 9 ? f = op_zjmp : 0;
	opcode == 10 ? f = op_ldi : 0;
	opcode == 11 ? f = op_sti : 0;
	opcode == 12 ? f = op_fork : 0;
	opcode == 13 ? f = op_lld : 0;
	opcode == 14 ? f = op_lldi : 0;
	opcode == 15 ? f = op_lfork : 0;
	opcode == 16 ? f = op_aff : 0;
	return (f);
}

static void	get_arguments(int instr_code, t_op *instr)
{
	int			i;
	static int	args[16][3] = {{T_DIR, 0, 0}, {T_DIR | T_IND, T_REG, 0},
	{T_REG, T_IND | T_REG, 0}, {T_REG, T_REG, T_REG}, {T_REG, T_REG, T_REG},
	{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, {T_DIR, 0, 0},
	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, {T_DIR, 0, 0},
	{T_DIR | T_IND, T_REG, 0}, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	{T_DIR, 0, 0}, {T_REG, 0, 0}};

	i = -1;
	while (++i < 3)
		instr->argv[i] = args[instr_code][i];
}

static t_op	get_instr(int instr_code)
{
	t_op		instr;
	static char	*instr_name[16] = {"live", "ld", "st", "add", "sub", "and",
	"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};
	static int	argc[16] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};
	static int	cycles[16] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, \
	50, 1000, 2};
	static int	labels[16] = {4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4};
	static int	encoding[16] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1};

	instr.instr_name = instr_name[instr_code];
	instr.argc = argc[instr_code];
	get_arguments(instr_code, &instr);
	instr.wait_cycles = cycles[instr_code];
	instr.instr_code = instr_code + 1;
	instr.dir_size = labels[instr_code];
	instr.encode = encoding[instr_code];
	instr.f = assign_opfunctions(instr_code + 1);
	return (instr);
}

void		get_op(t_op *op)
{
	int		i;

	i = 16;
	while (--i >= 0)
		op[i] = get_instr(i);
}
