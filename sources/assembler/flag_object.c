/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:07 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:10 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	Works as a sort of an object mock-up: flags variable is initially set
**	in check_args. After that get_flags() can be used to access the flags
**	info from anywhere without the need to pass a variable all over the place.
*/

static int	flag_object(int set, int flag_to_set)
{
	static int flags = 0;

	if (set)
		flags = flags | flag_to_set;
	return (flags);
}

void		set_flags(char c)
{
	if (ft_tolower(c) == 'h')
		flag_object(SET, FLAG_H);
	if (ft_tolower(c) == 'e')
		flag_object(SET, FLAG_E);
	if (ft_tolower(c) == 'r')
		flag_object(SET, FLAG_R);
	if (ft_tolower(c) == 'x')
		flag_object(SET, FLAG_X);
}

int			get_flags(void)
{
	return (flag_object(GET, 0));
}
