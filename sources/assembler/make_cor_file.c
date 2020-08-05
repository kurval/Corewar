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
		msg = merge_strs("Can't create file %s", c_filename);
		handle_error(msg);
		ft_strdel(&msg);
	}
	free(c_filename);
	return (fd);
}

void	insert_magic_header(int fd)
{
	int		magic;
	int		byte;
	char	output[4];
	int		i;

	magic = COREWAR_EXEC_MAGIC;
	i = 3;
	while (byte && i > -1)
	{
		byte = (magic & 0xFF);
		output[i] = (char)byte;
		magic = (magic >> 8);
		i--;
	}
	i = 0;
	while (i < 4)
	{
		ft_putchar_fd(output[i], fd);
		i++;
	}
}

void	make_cor_file(char *s_filename, t_asm assembler)
{
	int		fd;
	char	*msg;

	fd = open_corefile(s_filename, ft_strlen(s_filename) - 2);
	insert_magic_header(fd);
	if (close(fd) == -1)
	{
		msg = merge_strs("Can't close source file %s", s_filename);
		handle_error(msg);
		ft_strdel(&msg);
	}
}
