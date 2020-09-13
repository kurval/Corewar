/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 12:22:34 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/13 11:01:57 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_header(int src_file, int dest_file)
{
	int		i;
	int		j;
	int		len;
	char	*name_commet;
	char	character;

	i = -1;
	while (++i < 2)
	{
		j = 0;
		name_commet = i == 0 ? ".name \"" : ".comment \"";
		len = i == 0 ? PROG_NAME_LENGTH + 4 : COMMENT_LENGTH + 4;
		lseek(src_file, 4, SEEK_CUR);
		read(src_file, &character, 1);
		write(dest_file, name_commet, ft_strlen(name_commet));
		while (++j < len && character)
		{
			write(dest_file, &character, 1);
			read(src_file, &character, 1);
		}
		write(dest_file, "\"\n", ft_strlen("\"\n"));
		lseek(src_file, (len - j), SEEK_CUR);
	}
	write(dest_file, "\n", 1);
}

void		write_op_code(int input_file, int output_file)
{
	int op;
	int count;

	count = 0;
	op = 0;
	while ((op = write_operation(input_file, output_file)))
	{
		if (op > 15)
			handle_error("Error: Invalid .cor file");
		write_arguments(input_file, output_file, op);
		write(output_file, "\n", 1);
	}
}

char		*open_folder(char *folder, char *file)
{
	char	*final_name;
	int		i;
	int		j;

	final_name = ft_strnew(ft_strlen(folder) + 1 + ft_strlen(file));
	i = -1;
	j = -1;
	while (folder[++i])
		final_name[++j] = folder[i];
	final_name[++j] = '/';
	i = -1;
	while (file[++i])
		final_name[++j] = file[i];
	final_name[++j] = '\0';
	ft_strdel(&file);
	return (final_name);
}

void		dasm(char *src, const char *dest)
{
	int	src_file;
	int	dest_file;

	if ((src_file = open(src, O_RDONLY)) < 0)
		handle_error("ERROR: Unable to open file");
	if ((dest_file = open(dest, O_CREAT | O_RDWR, 0644)) < 0)
		handle_error("ERROR: Unable to create file");
	write_header(src_file, dest_file);
	write_op_code(src_file, dest_file);
	close(src_file);
	close(dest_file);
}
