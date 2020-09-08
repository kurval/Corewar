/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:17:07 by atuomine          #+#    #+#             */
/*   Updated: 2020/08/25 15:17:10 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_labels(t_label *labels)
{
	t_label *current;
	t_label *next;

	current = labels;
	while (current)
	{
		next = current->next;
		ft_strdel(&current->name);
		free(current);
		current = next;
	}
}

static void	free_stmts(t_stmt *stmts)
{
	t_stmt	*current;
	t_stmt	*next;
	int		i;

	current = stmts;
	while (current)
	{
		i = 0;
		next = current->next;
		ft_strdel(&current->name);
		while (current->args[i])
		{
			ft_strdel(&current->args[i]->content);
			free(current->args[i]->cursor);
			free(current->args[i]);
			i++;
		}
		free(current);
		current = next;
	}
}

static void	free_op(t_op *op)
{
	t_op *current;
	t_op *next;

	current = op;
	while (current)
	{
		next = current->next;
		free(current->argv);
		free(current);
		current = next;
	}
}

void		free_memory(t_op *op, t_champ *champ)
{
	free_op(op);
	ft_strdel(&champ->comment);
	ft_strdel(&champ->name);
	free_stmts(champ->stmts);
	free_labels(champ->labels);
}
