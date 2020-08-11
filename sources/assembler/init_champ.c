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

/*
** Set_champ
** The function sets the champion information (name, comment, labels and stmts
** (statements)) and done to one if name and comment have been saved.
** NOTE: The function is not yet complete. The sizes and places need to be saved
** in bytes and the saved strings might need to be saved differently.
*/

static t_arg	*get_arg(t_stmt *stmt, t_token *token)
{
	t_arg	*arg;

	if (!(arg = (t_arg *)malloc(sizeof(t_arg))) ||
	!(arg->content = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	arg->type = token->type;
	arg->size = 0;
	return (arg);
}

static void		set_stmt(t_champ *champ, t_token *token)
{
	t_stmt	*stmt;
	int		i;

	if (!(stmt = (t_stmt *)malloc(sizeof(t_stmt))) ||
	!(stmt->name = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	i = 0;
	while (token)
	{
		if (overlap((T_REG | T_DIR | T_IND), token->type))
			stmt->args[i++] = get_arg(stmt, token);
		token = token->next;
	}
	while (i < MAX_ARGS_NUMBER)
		stmt->args[i++] = NULL;
	stmt->size = 0;
	stmt->place = 0;
	if (!champ->stmts)
		stmt->next = NULL;
	else
		stmt->next = champ->stmts;
	champ->stmts = stmt;
}

static void		set_label(t_champ *champ, t_token *token)
{
	t_label *label;

	if (!(label = (t_label *)malloc(sizeof(t_label))) ||
	!(label->name = ft_strdup(token->content)))
		handle_error(MALLOC_ERROR);
	label->place = 0;
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
		set_stmt(champ, token);
	if (champ->name && champ->comment && !champ->done)
		champ->done = 1;
}

void			init_champ(t_champ *champ)
{
	champ->name = NULL;
	champ->comment = NULL;
	champ->labels = NULL;
	champ->stmts = NULL;
	champ->done = 0;
}
