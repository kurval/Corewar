/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 14:18:18 by jmetelin          #+#    #+#             */
/*   Updated: 2020/07/31 14:18:18 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define LIVE 1
#define LD 2
#define ST 3
#define ADD	4
#define SUB 5
#define AND 6
#define OR 7
#define XOR 8
#define ZJMP 9
#define LDI 10
#define STI 11
#define FORK 12
#define LLD 13
#define LLDI 14
#define LFORK 15
#define AFF 16

void		check_instr_args(int instrv, t_token **arg)
{
	t_token	*instr;
	char	*str;
	char	**strs;

	instr = arg;
	*arg = (*arg)->next;
	if (!*arg || ((instrv == LIVE || instrv == ZJMP || instrv == FORK ||
	instrv == LFORK) && (*arg)->type != DIRECT && (*arg)->type != DIRECT_LABEL) ||
	((instrv == LD || instrv == LLD) && (*arg)->type != DIRECT &&
	(*arg)->type != DIRECT_LABEL && (*arg)->type != INDIRECT &&
	(*arg)->type != INDIRECT_LABEL) ||
	((instrv == ST || instrv == ADD || instrv == SUB || instrv == STI ||
	instrv == AFF) && (*arg)->type != REGISTER) ||
	((instrv == AND || instrv == OR || instrv == XOR || instrv == LDI ||
	instrv == LLDI) && (*arg)->type != REGISTER && (*arg)->type != DIRECT &&
	(*arg)->type != DIRECT_LABEL && (*arg)->type != INDIRECT &&
	(*arg)->type != INDIRECT_LABEL))
	{
		if (!(strs = (char **)malloc(sizeof(char *) * 4)) ||
		!(strs[2] = ft_strdup(instr->content)))
			handle_error("Malloc error");
		strs[0] = i_to_padded_a(instr->cursor->row, 3);
		strs[1] = i_to_padded_a(instr->cursor->column, 3);
		strs[3] = NULL;
		str = merge_strs(
		"Syntax error at token [TOKEN] [%s:%s] INSTRUCTION \"%s\"", strs);
		del_array(&strs);
		handle_error(str);
		ft_strdel(&str);
	}
}

static int	get_instr_2(char *str, int *instr)
{
	if (ft_strequ(str, "zjmp"))
		*instr = ZJMP;
	else if (ft_strequ(str, "ldi"))
		*instr = LDI;
	else if (ft_strequ(str, "sti"))
		*instr = STI;
	else if (ft_strequ(str, "fork"))
		*instr = FORK;
	else if (ft_strequ(str, "lld"))
		*instr = LLD;
	else if (ft_strequ(str, "lldi"))
		*instr = LLDI;
	else if (ft_strequ(str, "lfork"))
		*instr = LFORK;
	else if (ft_strequ(str, "aff"))
		*instr = AFF;
}

int			get_instr(char *str)
{
	int	instr;

	instr = 0;
	if (ft_strequ(str, "live"))
		instr = LIVE;
	else if (ft_strequ(str, "ld"))
		instr = LD;
	else if (ft_strequ(str, "st"))
		instr = ST;
	else if (ft_strequ(str, "add"))
		instr = ADD;
	else if (ft_strequ(str, "sub"))
		instr = SUB;
	else if (ft_strequ(str, "and"))
		instr = AND;
	else if (ft_strequ(str, "or"))
		instr = OR;
	else if (ft_strequ(str, "xor"))
		instr = XOR;
	else
		get_instr_2(str, &instr);
	return (instr);
}

void		check_token_order(t_token *token)
{
	int	instr;

	while (token)
	{
		instr = 0;
		if (token->type == INSTRUCTION)
			instr = get_instr(token->content);
		if (instr)
		{
			token = token->next;
			check_instr_args(instr, &token);
		}
		token = token->next;
	}
}
