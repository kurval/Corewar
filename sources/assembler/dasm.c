/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 12:22:34 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/10 23:52:25 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

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

void		parse_file(int src_file, int dest_file)
{
	unsigned int *op;
	unsigned char character;

	while (read(src_file, &character, 1) > 0)
	{
		if (character >= 16)
			handle_error("ERROR: Cannot read file");
	}
}

void		dasm(char *src, const char *dest)
{
	int	src_file;
	int	dest_file;

	if ((src_file = open(src, O_RDONLY)) < 0)
		handle_error("ERROR: Unable to open file");
	dest_file = open(dest, O_CREAT | O_RDWR, 0644);
	write_header(src_file, dest_file);
}
