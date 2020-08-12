/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:49:51 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/12 14:35:24 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "corewar_error.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_arena
{
	unsigned char	arena[MEM_SIZE];
}					t_arena;

/*
**	Cursors contain following information:
**	id - unique.
**	carry - affects zjmp operation, initialised with value false.
**	current_opcode - operation code, before the battle starts it is not initialised.
**	cycle_live_reported - number of cycle in which current cursor performed operation live last time.
**	wait_cycles - amount of cycles to wait before operation execution.
**	current_position - address in memory
**	jump - amount of bytes cursor must jump to get to the next operation
**	reg[REG_NUMBER] - registries of current cursor
*/

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

/*
**	Players contain following information:
**	id - unique ID
**	name - champion name
**	comment[COMMENT_LENGTH + 1] - champion comment
**	executable_size - executable code size
**	code - executable code
*/

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

/*
**	Game parameters contain following information:
**	last_live_id - player last reported alive
**	>It is initialised with the highest player id,
**	>and is updated every time operation live is performed.
**	current_cycle - cycles counter
**	lives - counter for operation live, to check how many times
**	>this operation was performed during the last cycles_to_die cycles.
**	ctd - cycles_to_die — length of current check period in cycles.
**	>This variable is initialised with the value of constant CYCLES_TO_DIE (1536).
**	dump_cycle - number of cycle to dump memory (if present)
**	checks - amount of checks performed
*/

typedef struct		s_vm
{
	t_arena			*arena;
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
void    			init_arena(t_vm *vm, t_arena *arena);
void				print_arena(t_arena *arena);
void    			dump_memory(t_arena *arena);

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
