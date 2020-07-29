/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:02:03 by jmetelin          #+#    #+#             */
/*   Updated: 2020/07/29 17:02:07 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Handle_error
** 1. Print error msg followed by a \n to stderr
** 2. Exit with EXIT_FAILURE
*/

void	handle_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

char	*merge_strs(char *s1, char *s2, int place)
{
	char	*merged;
	int		i;

	if (!(merged = (char *)malloc(sizeof(char *) * (ft_strlen(s1) +
	ft_strlen(s2) + 1))))
		handle_error("Malloc error");
	i = 0;
	while (s1 && *s1 && i != place)
		merged[i++] = *s1++;
	while (s2 && *s2)
		merged[i++] = *s2++;
	while (s1 && *s1)
		merged[i++] = *s1++;
	merged[i] = '\0';
	return (merged);
}

/*
** Check_params
** 1. Check that there are two arguments (e.g. "./asm champ.s")
** 2. Check that the file has the extension .s
*/

void	check_params(int ac, char **av)
{
	char	*msg;
	int		i;

	if (ac != 2)
		handle_error("Usage: ./asm <sourcefile.s>");
	i = find_last_char(av[1], 0, "/");
	i++;
	if ((i = find_first_char(av[1], i, ".")) == -1 ||
	i != ft_strlen(av[1]) - 2 || av[1][i + 1] != 's')
	{
		msg = merge_strs("Source file  doesn't have the extension .s", av[1],
		12);
		handle_error(msg);
		ft_strdel(&msg);
	}
}
