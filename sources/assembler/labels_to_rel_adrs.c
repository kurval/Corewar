/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels_to_rel_adrs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:57:26 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/12 14:57:26 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	label_to_rel_adr(t_label *label, int stmt_place, t_arg *arg)
{
	char	*tmp;

	tmp = arg->content;
	while (*tmp != LABEL_CHAR)
		tmp++;
	tmp++;
	while (label && !ft_strnequ(label->name, tmp, ft_strlen(label->name) - 1))
		label = label->next;
	if (!label)
		handle_invalid_label(arg, tmp);
	arg->type = (arg->type == DIRECT_LABEL ? T_DIR : T_IND);
	if (!(tmp = ft_itoa(label->place - stmt_place)))
		handle_error(MALLOC_ERROR);
	ft_strdel(&arg->content);
	if (arg->type == T_DIR)
	{
		if (!(arg->content = ft_strjoin("%", tmp)))
			handle_error(MALLOC_ERROR);
		ft_strdel(&tmp);
	}
	else
		arg->content = tmp;
}

void		labels_to_rel_adrs(t_label *labels, t_stmt *stmt)
{
	int	i;

	while (stmt)
	{
		i = 0;
		while (stmt->args[i])
		{
			if (overlap(stmt->args[i]->type, ARG_LABEL))
				label_to_rel_adr(labels, stmt->place, stmt->args[i]);
			i++;
		}
		stmt = stmt->next;
	}
}
