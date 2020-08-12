/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:01:39 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/12 14:01:40 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_cursor		*copy_cursor(t_cursor cursor)
{
	t_cursor *new;

	new = (t_cursor *)malloc(sizeof(t_cursor));
	new->col = cursor.col;
	new->row = cursor.row;
	return (new);
}
