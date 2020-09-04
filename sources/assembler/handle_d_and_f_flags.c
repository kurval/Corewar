/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d_and_f_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 12:01:44 by jmetelin          #+#    #+#             */
/*   Updated: 2020/09/04 12:01:44 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	prefix_file_path(char **file_name, char *file_path, int end)
{
	char	*t1;
	char	*t2;

	if (!(t1 = ft_strsub(file_path, 0, end)))
		handle_error(MALLOC_ERROR);
	if (!(t2 = ft_strjoin(t1, *file_name)))
		handle_error(MALLOC_ERROR);
	ft_strdel(&t1);
	ft_strdel(&*file_name);
	*file_name = t2;
}

static void	replace_file_name(char **file, char *file_name)
{
	int	file_name_len;
	int	file_name_end;
	int	file_end;

	if ((file_name_len = ft_strlen(file_name)) -
	(file_name_end = find_last_str(file_name, file_name_len - 1, ".cor")) == 4)
	{
		if (!(file_name = file_name_end ?
		ft_strsub(file_name, 0, file_name_end) : ft_strdup("")))
			handle_error(MALLOC_ERROR);
	}
	else
	{
		if (!(file_name = ft_strdup(file_name)))
			handle_error(MALLOC_ERROR);
	}
	if (!ft_strchr(file_name, '/') &&
	(file_end = find_last_char(*file, ft_strlen(*file) - 1, "/") + 1))
		prefix_file_path(&file_name, *file, file_end);
	if (!(*file = ft_strjoin(file_name, ".s")))
		handle_error(MALLOC_ERROR);
	ft_strdel(&file_name);
}

static void	replace_file_path(char **file, char *file_path)
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

void		handle_d_and_f_flags(char **file)
{
	if (overlap(g_flags, flag_d))
	{
		replace_file_path(file, g_flag_d_arg);
		ft_strdel(&g_flag_d_arg);
	}
	if (overlap(g_flags, flag_f))
	{
		replace_file_name(file, g_flag_f_arg);
		ft_strdel(&g_flag_f_arg);
	}
}
