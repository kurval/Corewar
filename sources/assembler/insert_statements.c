#include "asm.h"

int		convert_label_location(char *name, t_label *labels, int stmt_place)
{
	// This is not ready
	return (10);
}

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

void	write_argument(t_arg *arg, int stmt_place, t_label *labels, int fd)
{
	int number;

	if (arg->type == T_REG)
		insert_bytes_number(fd, ft_atoi(&arg->content[1]), 1);
	else
	{
		if (overlap(arg->type, ARG_LABEL))
		{
			number = convert_label_location(arg->content, labels, stmt_place);
			insert_bytes_number(fd, number, arg->size);
		}
		else
		{
			number = (arg->type == T_DIR ? ft_atoi(&arg->content[1]) :
			ft_atoi(arg->content));
			insert_bytes_number(fd, ft_atoi(&arg->content[1]), arg->size);
		}
	}
}

void	write_statement(t_stmt *stmt, int fd, t_label *labels)
{
	int i;

	insert_bytes_number(fd, stmt->instr_code, 1);
	if (stmt->arg_code)
		insert_bytes_number(fd, stmt->arg_code, 1);
	i = 0;
	while (stmt->args[i])
	{
		write_argument(stmt->args[i], stmt->place, labels, fd);
		i++;
	}
}

void	insert_statements(t_champ champ, t_op *op, int fd)
{
	t_stmt	*statement;
	char	*bytes;

	statement = champ.stmts;
	while (statement)
	{
		statement->arg_code = get_arg_code(statement);
		statement->instr_code = get_instr_code(statement, op);
		write_statement(statement, fd, champ.labels);
		statement = statement->next;
	}
}