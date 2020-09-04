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

static int	validate_flag(char *str)
{
	int i;

	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
		{
			if (ft_strchr(FLAG_CHARS, ft_tolower(str[i])))
				set_flags(str[i]);
			else
				handle_error("Invalid flags");
			i++;
		}
		return (1);
	}
	return (0);
}

/*
** Process_arg
** Checks whether argument has .s in the end. If not,
** we test whether the argument is a valid flag.
** If both are false, file name error is printed. Otherwise
** argument is either saved as a source file or saved as flags.
** In case of a second .s file argument is encountered, multiple
** .s file error is printed.
** "-h.s" would be treated as a valid .s file.
*/

void		process_arg(char *argv, char **source)
{
	int		len;
	int		dot_loc;
	char	*msg;

	len = ft_strlen(argv);
	dot_loc = find_last_char(argv, len - 1, ".");
	if (dot_loc == -1 || dot_loc != len - 2 || argv[dot_loc + 1] != 's')
	{
		if (!validate_flag(argv))
		{
			msg = add_str_to_str("Src file %s doesn't have the extension .s",
			argv);
			handle_error(msg);
		}
	}
	else
	{
		if (*source)
			handle_error("Can only specify one source file.");
		else if (!(*source = ft_strdup(argv)))
			handle_error(MALLOC_ERROR);
	}
}

/*
** Check_args
** 1. Check that there are are arguments
** 2. Checks each argument with process_arg (read above)
*/

char		*check_args(int argc, char **argv, char **dest)
{
	char	*msg;
	int		len;
	int		i;
	int		dot_loc;
	char	*source;

	source = NULL;
	if (argc < 2)
		return (NULL);
	g_flags = 0;
	g_flag_d_arg = NULL;
	i = 1;
	while (i < argc)
	{
		if (overlap(g_flags, flag_d) && !g_flag_d_arg)
			g_flag_d_arg = argv[i];
		else
			process_arg(argv[i], &source);
		i++;
	}
	if (overlap(g_flags, flag_d) && !g_flag_d_arg)
		handle_error("Option requires an argument -- 'd'");
	return (source);
}
