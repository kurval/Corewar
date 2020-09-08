/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:07 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:10 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	toggle_error_debug_flag(void)
{
	if (g_flags & flag_error_debug)
		g_flags = g_flags ^ flag_error_debug;
	else
		g_flags = g_flags | flag_error_debug;
}

void	set_flags(char c)
{
	int	*ptr;

	ptr = &g_flags;
	if (ft_tolower(c) == 'h')
		*ptr = g_flags | flag_h;
	if (ft_tolower(c) == 'e')
		*ptr = g_flags | flag_e;
	if (ft_tolower(c) == 'd')
		*ptr = g_flags | flag_d;
	if (ft_tolower(c) == 'x')
		*ptr = g_flags | flag_x;
	if (ft_tolower(c) == 'f')
		*ptr = g_flags | flag_f;
}
