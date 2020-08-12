/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 16:37:28 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/11 16:37:28 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Set_champ
** The function sets the champion information (name, comment, labels and stmts
** (statements)) and done to one if name and comment have been saved.
*/

static t_arg	*get_arg(char *stmt_name, t_token *token)
{
	t_arg	*arg;

	if (!(arg = (t_arg *)malloc(sizeof(t_arg))) ||
	!(arg->content = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	arg->type = token->type;
	if (overlap(T_REG, token->type))
		arg->size = 1;
	else if (overlap(T_IND, token->type) || (overlap(T_DIR, token->type) &&
	(ft_strequ("zjmp", stmt_name) || ft_strequ("ldi", stmt_name) ||
	ft_strequ("sti", stmt_name) || ft_strequ("fork", stmt_name) ||
	ft_strequ("lldi", stmt_name) || ft_strequ("lfork", stmt_name))))
		arg->size = 2;
	else
		arg->size = 4;
	return (arg);
}

static void		set_args(t_stmt *stmt, t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (overlap((T_REG | T_DIR | T_IND), token->type))
		{
			stmt->args[i] = get_arg(stmt->name, token);
			stmt->size += stmt->args[i++]->size;
		}
		token = token->next;
	}
	while (i < MAX_ARGS_NUMBER)
		stmt->args[i++] = NULL;
}

static void		set_stmt(t_champ *champ, t_token *token)
{
	t_stmt	*stmt;

	if (!(stmt = (t_stmt *)malloc(sizeof(t_stmt))) ||
	!(stmt->name = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	stmt->size = 1;
	if (!ft_strequ("live", stmt->name) && !ft_strequ("zjmp", stmt->name) &&
	!ft_strequ("fork", stmt->name) && !ft_strequ("lfork", stmt->name))
		stmt->size += 1;
	set_args(stmt, token->next);
	if (!champ->stmts)
	{
		stmt->place = 0;
		stmt->next = NULL;
	}
	else
	{
		stmt->place = champ->stmts->place + champ->stmts->size;
		stmt->next = champ->stmts;
	}
	champ->stmts = stmt;
}

static void		set_label(t_champ *champ, t_token *token)
{
	t_label *label;

	if (!(label = (t_label *)malloc(sizeof(t_label))) ||
	!(label->name = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	label->place = -1;
	if (!champ->labels)
		label->next = NULL;
	else
		label->next = champ->labels;
	champ->labels = label;
}

void			set_champ(t_champ *champ, t_token *token)
{
	if (token->type == COMMAND_NAME)
	{
		token = token->next;
		if (!(champ->name = ft_strdup(token->content)))
			handle_error(MALLOC_ERROR);
	}
	else if (token->type == COMMAND_COMMENT)
	{
		token = token->next;
		if (!(champ->comment = ft_strdup(token->content)))
			handle_error(MALLOC_ERROR);
	}
	else if (token->type == LABEL)
	{
		set_label(champ, token);
		token = token->next;
	}
	if (token->type == INSTRUCTION)
	{
		set_stmt(champ, token);
		if (champ->labels && champ->labels->place == -1)
			champ->labels->place = champ->stmts->place;
	}
	if (champ->name && champ->comment && !champ->done)
		champ->done = 1;
}
