/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_file_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 12:01:44 by jmetelin          #+#    #+#             */
/*   Updated: 2020/09/04 12:01:44 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	replace_file_path(char **file, char *file_path)
{
	char	*t1;
	char	*t2;
	int		len;
	int		start;

	len = ft_strlen(*file);
	if ((start = find_last_char(*file, len - 1, "/") + 1))
	{
		if (!(t1 = ft_strsub(*file, start, len - start)))
			handle_error(MALLOC_ERROR);
		ft_strdel(&*file);
	}
	else
		t1 = *file;
	if (file_path[ft_strlen(file_path) - 1] != '/')
	{
		t2 = t1;
		if (!(t1 = ft_strjoin("/", t2)))
			handle_error(MALLOC_ERROR);
		ft_strdel(&t2);
	}
	if (!(*file = ft_strjoin(file_path, t1)))
		handle_error(MALLOC_ERROR);
	ft_strdel(&t1);
}
