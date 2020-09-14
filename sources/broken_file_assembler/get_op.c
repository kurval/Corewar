/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:52:15 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/12 16:50:26 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
		handle_error("Malloc error");
	while (--argc >= 0)
		args[argc] = argv[instr_code - 1][argc];
	return (args);
}

static t_op	*get_instr(int instr_code)
{
	t_op		*instr;
	static char	*instr_name[16] = {"live", "ld", "st", "add", "sub", "and",
	"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};
	static int	argc[16] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};

	if (!(instr = (t_op *)malloc(sizeof(t_op))))
		handle_error("Malloc error");
	instr->instr_name = instr_name[instr_code - 1];
	instr->argc = argc[instr_code - 1];
	instr->argv = get_args(instr_code, argc[instr_code - 1]);
	instr->instr_code = instr_code;
	instr->next = NULL;
	return (instr);
}

t_op		*get_op(void)
{
	t_op	*op;
	t_op	*new;
	int		i;

	op = NULL;
	i = 16;
	while (i > 0)
	{
		new = get_instr(i--);
		if (op)
			new->next = op;
		op = new;
	}
	return (op);
}
