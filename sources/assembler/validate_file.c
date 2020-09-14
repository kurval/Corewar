/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 11:47:45 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/13 10:30:43 by bkonjuha         ###   ########.fr       */
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

char		*validate_file(char *file)
{
	char	*new_file;
	char	*filename;
	int		len;

	filename = ft_strrchr(file, '/');
	filename = filename == NULL ? file : filename + 1;
	len = ends_with_cor(filename);
	new_file = ft_strnew(len + 2);
	ft_strncpy(new_file, filename, len);
	ft_strcat(new_file, ".s");
	return (new_file);
}
