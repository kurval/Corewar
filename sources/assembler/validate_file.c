/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 11:47:45 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/22 08:23:44 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ends_with_cor(char *file)
{
	int		i;

	i = 0;
	while (file[i])
		i++;
	if (!ft_strequ(file + i - 4, ".cor"))
		handle_error("ERROR: Invalid extensions");
	return (i - 4);
}

static void	is_correct_length(char *file)
{
	int fd;

	fd = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		handle_error("Error: Unable to open file");
	if (lseek(fd, 0, SEEK_END) < (long long)sizeof(t_header))
		handle_error("Error: File is missing mandatory fields or is too small");
	close(fd);
}

static void	has_magic_header(char *file)
{
	int fd;

	fd = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		handle_error("Error: Unable to open file");
	if (read_n_bytes(fd, 4) != COREWAR_EXEC_MAGIC)
		handle_error("Error: File is missing magic header");
	close(fd);
}

char		*validate_file(char *file)
{
	char	*new_file;
	char	*filename;
	int		len;

	is_correct_length(file);
	has_magic_header(file);
	filename = ft_strrchr(file, '/');
	filename = filename == NULL ? file : filename + 1;
	len = ends_with_cor(filename);
	new_file = ft_strnew(len + 2);
	ft_strncpy(new_file, filename, len);
	ft_strcat(new_file, ".s");
	return (new_file);
}
