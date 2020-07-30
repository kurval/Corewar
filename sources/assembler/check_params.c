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

void		handle_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/*
** Merge_strs
** 1. Count the len of s1 without "%" and "%s".
** 2. Allocate memory for merged of size: the counted len of s1 + the len of s2.
** 3. Copy s1 to merged char by char until '%' is found.
** 4. A) '%' is found: If the next char is 's', copy s2 to merged. If the char
**                     is NOT 's', copy the char to merged. If there is s1 left,
**                     copy the rest of s1 to merged.
**    B) '%' is NOT found: Copy s2 to the end of merged.
*/

static int	count_s1_len(char *s1)
{
	int	s1_len;

	s1_len = 0;
	while (s1 && *s1)
	{
		if (*s1 == '%')
		{
			if (++s1 && *s1 == 's')
				s1++;
		}
		else
		{
			s1_len++;
			s1++;
		}
	}
	return (s1_len);
}

char		*merge_strs(char *s1, char *s2)
{
	char	*merged;
	int		i;

	if (!(merged = (char *)malloc(sizeof(char *) * (count_s1_len(s1) +
	ft_strlen(s2) + 1))))
		handle_error("Malloc error");
	i = 0;
	while (s1 && *s1)
	{
		if (*s1 == '%' && ++s1 && *s1 == 's')
		{
			while (s2 && *s2)
				merged[i++] = *s2++;
			s1++;
		}
		else if (*s1)
			merged[i++] = *s1++;
	}
	while (s2 && *s2)
		merged[i++] = *s2++;
	merged[i] = '\0';
	return (merged);
}

/*
** Check_params
** 1. Check that there are two arguments (e.g. "./asm champ.s")
** 2. Check that the file has the extension .s
*/

void		check_params(int ac, char **av)
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
		msg = merge_strs("Source file %s doesn't have the extension .s", av[1]);
		handle_error(msg);
		ft_strdel(&msg);
	}
}
