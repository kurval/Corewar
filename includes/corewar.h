/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:49:51 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/28 11:57:59 by vkurkela         ###   ########.fr       */
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
# include <ncurses.h>

# define MASK1 192
# define MASK2 48
# define MASK3 12

# define RED	"\033[1m\033[31m"
# define GREEN	"\033[1m\033[32m"
# define RESET	"\033[0m"

typedef struct		s_arena
{
	unsigned char	arena[MEM_SIZE];
	int				owner[MEM_SIZE];
}					t_arena;

/*
** Cursors contain following information:
** - id : unique.
** - carry : affects zjmp operation, initialised with value false.
** - opcode: operation code, before the battle starts it is not initialised.
** - last_live : number of cycle in which current cursor performed operation
** 	>live last time.
** - wait_cycles : amount of cycles to wait before operation execution.
** - pc : current position address in memory
** - jump : amount of bytes cursor must jump to get to the next operation
** - reg[REG_NUMBER] : registries of current cursor
** - args[3] : current cursors argument types
** - values[3] : current cursors argument values
**	>T_REG registry number
**	>T_DIR A number, saved on 2 or 4 bytes, depending on label
**	>T_IND relative address number
*/

typedef struct		s_process
{
	int				args[3];
	int				values[3];
	unsigned int	id;
	unsigned int	carry;
	unsigned int	opcode;
	unsigned int	last_live;
	unsigned int	wait_cycles;
	unsigned int	pc;
	int				jump;
	int				reg[REG_NUMBER];
	unsigned int	player_id;
	void			*player;
	struct s_process*next;
}					t_process;

/*
** Players contain following information:
** - id : unique ID
** - name : champion name
** - comment[COMMENT_LENGTH + 1]:  champion comment
** - executable_size : executable code size
** - code : executable code
** - Other information can be found in op.h header struct
*/

typedef struct		s_player
{
	int				id;
	char			code[CHAMP_MAX_SIZE];
	header_t		h;
}					t_player;

/*
** Game parameters contain following information:
** - last_live_id : player last reported alive
** 	>It is initialised with the highest player id,
** 	>and is updated every time operation live is performed.
** - current_cycle : cycles counter
** - lives : counter for operation live, to check how many times
** 	>this operation was performed during the last cycles_to_die cycles.
** - ctd (cycles_to_die) : length of current check period in cycles.
** 	>This variable is initialised with the value of constant CYCLES_TO_DIE
**  (1536).
** - dump_cycle : number of cycle to dump memory (if present)
** - checks : amount of checks performed
** - cycles : is used to track periods
** - operations : list of all operations and info of each one
** - nb_players : number of champions
** - nb_procs : number of process
*/

typedef struct		s_vm
{
	t_arena			*a;
	t_player		p[MAX_PLAYERS];
	struct s_op		*operations;
	unsigned int	last_live_id;
	unsigned int	cycles;
	unsigned int	cycles_to_die;
	unsigned int	current_cycle;
	unsigned int	checks;
	unsigned int	lives;
	int				ctd;
	unsigned int	dump_cycle;
	int				a_flag;
	unsigned int	nb_players;
	unsigned int	nb_procs;
	unsigned int	id_counter;
	t_process		*proc_list;
}					t_vm;

/*
** Operations contain following information:
** - instr_name : operation name
** - argc : number of arguments
** - argv : arguments tab
** - instr_code : operation code
** - wait_cycles : cycles untill execution
** - dir_size : 2 or 4 bytes
** - encode : 1 present 0 no encoding byte
*/

typedef struct		s_op
{
	char			*instr_name;
	int				argc;
	int				argv[3];
	unsigned int	instr_code;
	unsigned int	wait_cycles;
	unsigned int	dir_size;
	unsigned int	encode;
	void			(*f)(t_vm *vm, t_process *proc);
}					t_op;

/*
**					VM FUNCTIONS
*/

void				init_vm(t_vm *vm);
void				run_cycles(t_vm *vm);
void    			init_arena(t_vm *vm, t_arena *arena);
void				print_arena(t_arena *arena);
void				dump_memory(t_vm *vm);

/*
**					HELPER FUNCTIONS
*/

void				ft_errno(char *id);
void				get_op(t_op *op);
int					validate_encoding(t_vm *vm, int encode_byte, t_process *proc);
void				free_all(t_vm *vm);
void				*assign_opfunctions(int opcode);
int					get_addr(int addr);
int					get_args(t_vm *vm, t_process *proc);
void				remove_proc(t_vm *vm, t_process **proc_list, t_process **current, t_process **previous);
int					int_arg(t_vm *vm, int idx);
int					get_op_values(t_vm *vm, t_process *proc, int arg);
void				load_into_memory(t_vm *vm, unsigned int addr, void *content);
void    			init_processes(t_vm *vm);
void				decleare_winner(t_vm *vm);
void				add_to_list(t_process *new, t_process **list);
t_process			*new_proc();
t_process			*copy_proc(t_vm *vm, t_process *og_proc);

/*
**					PARSE INPUT FUNCTIONS
*/

void				validate_chapions(char **s);
void				parse_input(int ac, char **av, t_vm *vm);
void				load_champions(t_vm *vm);
void				get_dump(t_vm *vm, char *s);

/*
**					OPERATION FUNCTIONS
*/

void				op_add(t_vm *vm, t_process *proc);
void				op_aff(t_vm *vm, t_process *proc);
void				op_and(t_vm *vm, t_process *proc);
void				op_fork(t_vm *vm, t_process *proc);
void				op_ld(t_vm *vm, t_process *proc);
void				op_ldi(t_vm *vm, t_process *proc);
void				op_lfork(t_vm *vm, t_process *proc);
void				op_live(t_vm *vm, t_process *proc);
void				op_lld(t_vm *vm, t_process *proc);
void				op_lldi(t_vm *vm, t_process *proc);
void				op_or(t_vm *vm, t_process *proc);
void				op_st(t_vm *vm, t_process *proc);
void				op_sti(t_vm *vm, t_process *proc);
void				op_sub(t_vm *vm, t_process *proc);
void				op_xor(t_vm *vm, t_process *proc);
void				op_zjmp(t_vm *vm, t_process *proc);

/*
**					VISUALIZER
*/

void				init_visualizer(void);

#endif
