/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:49:51 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/07/29 16:11:28 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"

typedef struct		s_arena
{
	unsigned char	arena[MEM_SIZE];
}					t_arena;

typedef struct		s_process
{
	int				id;
	int				carry;
	unsigned int	current_opcode;
	int				cycle_live_reported;
	int				wait_cycles;
	int				current_position;
	int				jump;
	int				reg[REG_NUMBER];
	int				cycles;
	int				live;
	char			*p_name;
	t_process		*next;
}					t_process;


typedef struct		s_player
{
	int				id;
	char			*name;
	char			*comment;
	int				executable_size;
	char			*code;
	int				live;
	t_process		proc;
}					t_player;

typedef struct		s_vm
{
	t_arena			a;
	t_player		p[MAX_PLAYERS];
	int				last_live_id;
	int				cycles;
	int				current_cycle;
	int				checks;
}					t_vm;

#endif
