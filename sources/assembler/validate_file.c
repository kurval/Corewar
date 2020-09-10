/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 11:47:45 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/02 12:24:42 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

int		ends_with_cor(char *file)
{
	int		i;

	i = 0;
	while (file[i])
		i++;
	if (!ft_strequ(file + i - 4, ".cor"))
		handle_error("ERROR: Invalid extensions");
	return (i - 4);
}

char	*validate_file(char *file)
{
	char	*new_file;
	char	*filename;
	int		len;

	filename = ft_strrchr(file, '/');
	filename = filename == NULL ? file : filename;
	len = ends_with_cor(filename + 1);
	new_file = ft_strnew(len + 2);
	ft_strncpy(new_file, filename + 1, len);
	ft_strcat(new_file, ".s");
	return (new_file);
}
