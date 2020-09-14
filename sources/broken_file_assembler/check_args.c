/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:02:03 by jmetelin          #+#    #+#             */
/*   Updated: 2020/07/29 17:02:07 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Process_arg
** Check if the argument has .s in the end. If not, print the file name error.
** Otherwise, save the argument as a source file. In case of a second .s file
** argument, print the multiple .s file error.
*/

static void	process_arg(char *argv, char **source)
{
	int		len;
	int		dot_loc;
	char	*msg;

	len = ft_strlen(argv);
	dot_loc = find_last_char(argv, len - 1, ".");
	if (dot_loc == -1 || dot_loc != len - 2 || argv[dot_loc + 1] != 's')
	{
		msg = add_str_to_str("Src file %s doesn't have the extension .s", argv);
		handle_error(msg);
	}
	else
	{
		if (*source)
			handle_error("Can only specify one source file.");
		else if (!(*source = ft_strdup(argv)))
			handle_error(MALLOC_ERROR);
	}
}

static void	validate_flag(char ***strs)
{
	while (*++(**strs))
	{
		if (ft_strchr(FLAG_CHARS, ft_tolower(***strs)))
			set_flags(***strs);
		else
			handle_error("Invalid flags");
		if (***strs == 'd')
		{
			validate_d_and_f_flags(strs, ***strs, &g_flag_d_arg);
			break ;
		}
		else if (***strs == 'f')
		{
			validate_d_and_f_flags(strs, ***strs, &g_flag_f_arg);
			break ;
		}
	}
}

/*
** Check_args
** 1. Check that there are arguments
** 2.1 If the argument starts with '-', checked it with validate_flag function
** 2.2 Else, check the argument with process_arg function (read above)
*/

char		*check_args(int argc, char **argv, char **dest)
{
	char	*msg;
	int		len;
	int		dot_loc;
	char	*source;

	source = NULL;
	if (argc < 2)
		return (NULL);
	g_flags = 0;
	g_flag_d_arg = NULL;
	g_flag_f_arg = NULL;
	while (*++argv)
	{
		if (**argv == '-')
			validate_flag(&argv);
		else
			process_arg(*argv, &source);
	}
	return (source);
}
