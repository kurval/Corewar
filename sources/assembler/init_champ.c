/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:52:08 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/10 15:52:08 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_champ(t_champ *champ)
{
	champ->name = NULL;
	champ->comment = NULL;
	champ->labels = NULL;
	champ->stmts = NULL;
	champ->done = 0;
}
