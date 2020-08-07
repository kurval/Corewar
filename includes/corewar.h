/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:49:51 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/07 14:34:53 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "corewar_error.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/printf/includes/printf.h"
# include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	int				executable_size;
	char			*code;
	int				live;
	//				Meant for T_Header VVVV
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	//				Meant for t_header /\/\/
	header_t		header;
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
	int				lives;
	int				ctd;
	int				dump_cycle;
}					t_vm;

/*
**					VM FUNCTIONS
*/

void				init_vm(t_vm *vm);
void				run_cycles(t_vm *cor);

/*
**					HELPER FUNCTIONS
*/

void				ft_errno(char *id);

/*
**					PARSE INPUT FUNCTIONS
*/

void				validate_chapions(char **s);

void				parse_input(char **av, t_vm *vm);

#endif
