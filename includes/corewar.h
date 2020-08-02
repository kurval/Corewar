/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:49:51 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/02 16:56:16 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "corewar_error.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

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
	void			*next;
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

/*
**					VM FUNCTIONS
*/

t_vm				*init_vm(void);

/*
**					HELPER FUNCTIONS
*/

void				ft_errno(char *id);

#endif
