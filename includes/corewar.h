/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:49:51 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/07/29 10:02:10 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# define MEM_SIZE 4096
# define PLAYERS 4

typedef struct		s_arena
{
	unsigned char	arena[MEM_SIZE];
}					t_arena;

typedef struct		s_process
{
	char			*p_name;
	int				cycles;
	int				live;
	t_process		*next;
}					t_process;


typedef struct		s_player
{
	char			*name;
	char			*comment;
	char			*code;
	int				live;
	t_process		proc;
}					t_player;

typedef struct		s_vm
{
	t_arena			a;
	t_player		p[PLAYERS];
	int				cycles;
	int				current_cycle;
}					t_vm;

#endif
