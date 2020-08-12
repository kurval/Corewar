/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 14:01:39 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/11 14:01:40 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_bin_code(t_arg *arg)
{
	if (overlap(arg->type, T_REG))
		return ("01");
	else if (overlap(arg->type, T_DIR))
		return ("10");
	else if (overlap(arg->type, T_IND))
		return ("11");
	else
		return ("00");
}

int			needs_arg_code(t_stmt *stmt)
{
	if (!ft_strequ("live", stmt->name) && !ft_strequ("zjmp", stmt->name) &&
		!ft_strequ("fork", stmt->name) && !ft_strequ("lfork", stmt->name))
		return (1);
	else
		return (0);
}

int			get_arg_code(t_stmt *stmt)
{
	int		i;
	int		bit_loc;
	char	*binary;

	if (needs_arg_code(stmt))
	{
		binary = ft_strnew(8);
		i = 0;
		bit_loc = 0;
		while (bit_loc < 8)
		{
			if (stmt->args[i] && i < MAX_ARGS_NUMBER)
				ft_strcpy(&binary[bit_loc], get_bin_code(stmt->args[i]));
			else
				ft_strcpy(&binary[bit_loc], "00");
			bit_loc = bit_loc + 2;
			i++;
		}
		return (convert_dec(binary, 8));
	}
	else
		return (0);
}
