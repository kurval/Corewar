/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_statements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:01:39 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/12 14:01:40 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_instr_code(t_stmt *statement, t_op *op)
{
	while (op)
	{
		if (ft_strequ(op->instr_name, statement->name))
			return (op->instr_code);
		op = op->next;
	}
	return (-1);
}

void	write_argument(t_arg *arg, t_label *labels, int fd, int state)
{
	int number;

	if (arg->type == T_REG)
		insert_bytes_number(fd, ft_atoi(&arg->content[1]), 1, state);
	else
	{
		number = (arg->type == T_DIR ? ft_atoi(&arg->content[1]) :
		ft_atoi(arg->content));
		insert_bytes_number(fd, number, arg->size, state);
	}
}

void	write_statement(t_stmt *stmt, int fd, t_label *labels, int state)
{
	int i;

	insert_bytes_number(fd, stmt->instr_code, 1, state);
	if (stmt->arg_code)
		insert_bytes_number(fd, stmt->arg_code, 1, state);
	i = 0;
	while (stmt->args[i])
	{
		write_argument(stmt->args[i], labels, fd, state);
		i++;
	}
}

void	print_args(t_stmt *stmt)
{
	int i;

	i = 0;
	while (stmt->args[i])
	{
		ft_printf("arg %d: %s ", i, stmt->args[i]->content);
		i++;
	}
	ft_printf("\n");
}

void	insert_statements(t_stmt *stmt, t_label *labels, t_op *op, int fd)
{
	char		*bytes;
	static int	state = STATE_STMT;

	if (stmt)
	{
		if (stmt->next)
			insert_statements(stmt->next, labels, op, fd);
		stmt->arg_code = get_arg_code(stmt);
		stmt->instr_code = get_instr_code(stmt, op);
		write_statement(stmt, fd, labels, state);
		stmt = stmt->next;
		state = (state == STATE_STMT ? STATE_STMT + 1 : STATE_STMT);
	}
}
