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

int		open_corefile(char *s_filename, int filename_len)
{
	char	*c_filename;
	int		fd;
	char	*msg;

	c_filename = ft_strnew(filename_len + 5);
	c_filename = ft_strncpy(c_filename, s_filename, filename_len);
	ft_strcpy(&c_filename[filename_len], ".cor");
	c_filename[filename_len + 4] = '\0';
	if ((fd = open(c_filename, O_WRONLY | O_CREAT, 0755)) == -1)
	{
		msg = add_str_to_str("Can't create file %s", c_filename);
		handle_error(msg);
	}
	free(c_filename);
	return (fd);
}

void	make_cor_file(char *s_filename, t_asm assembler)
{
	int		fd;
	char	*msg;

	fd = open_corefile(s_filename, ft_strlen(s_filename) - 2);
	insert_bytes_number(fd, COREWAR_EXEC_MAGIC, 4); //magic header
	//insert champion info, remember null and exec-code-size
	insert_statements(assembler.champ, assembler.op, fd);
	if (close(fd) == -1)
	{
		msg = add_str_to_str("Can't close source file %s", s_filename);
		handle_error(msg);
	}
}
