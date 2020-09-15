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

/*
**	Inserts a string (string) in a file (fd). If str length
**	is lower than size, the rest is padded with null bytes.
*/

static void	insert_bytes_string(int fd, char *str, int size,
t_state state)
{
	int strlen;
	int	byte_nbr;

	strlen = ft_strlen(str);
	byte_nbr = write(fd, str, strlen);
	if (overlap(g_flags, flag_x))
		write_hexdump((unsigned char *)str, byte_nbr, state);
	size = size - strlen;
	if (size > 0)
		insert_bytes_number(fd, 0, size, state);
}

static void	insert_champion_info(t_champ champ, int fd)
{
	int	exec_code_size;

	exec_code_size = 0;
	if (champ.name)
	insert_bytes_string(fd, champ.name, PROG_NAME_LENGTH, name);
	insert_bytes_number(fd, 0, 4, 0);
	if (champ.stmts)
		exec_code_size = champ.stmts->place + champ.stmts->size;
	insert_bytes_number(fd, exec_code_size, 4, exec);
	if (champ.comment)
	insert_bytes_string(fd, champ.comment, COMMENT_LENGTH, comment);
	insert_bytes_number(fd, 0, 4, 0);
}

static int	open_corefile(char *s_filename, int filename_len)
{
	char	*c_filename;
	int		fd;
	char	*msg;

	if (!(c_filename = ft_strnew(filename_len + 5)))
		handle_error(MALLOC_ERROR);
	c_filename = ft_strncpy(c_filename, s_filename, filename_len);
	ft_strcpy(&c_filename[filename_len], ".cor");
	c_filename[filename_len + 4] = '\0';
	if ((fd = open(c_filename, O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1)
	{
		msg = add_str_to_str("Can't create file %s", c_filename);
		handle_error(msg);
	}
	ft_printf("Writing output program to %s\n", c_filename);
	free(c_filename);
	free(s_filename);
	return (fd);
}

void		make_cor_file(char *s_filename, t_asm assembler)
{
	int		fd;
	char	*msg;

	fd = open_corefile(s_filename, ft_strlen(s_filename) - 2);
	insert_bytes_number(fd, COREWAR_EXEC_MAGIC, 4, magic);
	insert_champion_info(assembler.champ, fd);
	if (assembler.champ.stmts)
		insert_statements(assembler.champ.stmts, assembler.champ.labels,
	assembler.op, fd);
	if (overlap(g_flags, flag_x))
		write_hexdump(NULL, 0, finish);
	if (close(fd) == -1)
	{
		msg = add_str_to_str("Can't close source file %s", s_filename);
		handle_error(msg);
	}
}
