/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:48:21 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/13 10:48:21 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_str_len(char *name, char *comment)
{
	char	*msg;
	char	*max_len;

	if (ft_strlen(name) > PROG_NAME_LENGTH)
	{
		if (!(max_len = ft_itoa(PROG_NAME_LENGTH)))
			handle_error(MALLOC_ERROR);
		msg = add_str_to_str("Champion name too long (Max length %s)", max_len);
		ft_strdel(&max_len);
		handle_error(msg);
	}
	else if (ft_strlen(comment) > COMMENT_LENGTH)
	{
		if (!(max_len = ft_itoa(COMMENT_LENGTH)))
			handle_error(MALLOC_ERROR);
		msg = add_str_to_str("Champion comment too long (Max length %s)",
		max_len);
		ft_strdel(&max_len);
		handle_error(msg);
	}
}
