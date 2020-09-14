/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:19 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:21 by atuomine         ###   ########.fr       */
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
	while (label && !ft_strequ(label->name, tmp))
		label = label->next;
	if (!label)
	{
		handle_invalid_label(arg, tmp);
		return ;
	}
	arg->type = (arg->type == direct_label ? T_DIR : T_IND);
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
			if (overlap(stmt->args[i]->type, arg_label))
				label_to_rel_adr(labels, stmt->place, stmt->args[i]);
			i++;
		}
		stmt = stmt->next;
	}
}

void		check_str_len(char *name, char *comment)
{
	char	*msg;
	char	*max_len;

	if (name && ft_strlen(name) > PROG_NAME_LENGTH)
	{
		if (!(max_len = ft_itoa(PROG_NAME_LENGTH)))
			handle_error(MALLOC_ERROR);
		msg = add_str_to_str("Champion name too long (Max length %s)", max_len);
		ft_strdel(&max_len);
		handle_error_free_msg(msg);
	}
	else if (comment && ft_strlen(comment) > COMMENT_LENGTH)
	{
		if (!(max_len = ft_itoa(COMMENT_LENGTH)))
			handle_error(MALLOC_ERROR);
		msg = add_str_to_str("Champion comment too long (Max length %s)",
		max_len);
		ft_strdel(&max_len);
		handle_error_free_msg(msg);
	}
}

/*
**	Fixes label place for the following cases:
**		- Multiple labels in a row
**		- Label at the end of file
*/

void		fix_label_place(t_champ *champ)
{
	if (champ->labels && champ->labels->place == -1)
	{
		if (!champ->stmts)
			champ->labels->place = 0;
		else
			champ->labels->place = champ->stmts->place + champ->stmts->size;
	}
}
