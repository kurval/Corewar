/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 09:49:51 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/31 19:40:44 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "visu.h"
# include "corewar_error.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define MASK1 192
# define MASK2 48
# define MASK3 12

# define UINT_MAX 4294967295

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
	struct s_player	*player;
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
** - last_live : last cycle players was alive
** - period_lives: number of lives in current period
*/

typedef struct		s_player
{
	int				id;
	char			code[CHAMP_MAX_SIZE];
	unsigned int	last_live;
	unsigned int	period_lives;
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
	unsigned int	current_cycle;
	unsigned int	checks;
	unsigned int	lives;
	int				ctd;
	unsigned int	dump_cycle;
	int				a_flag;
	int				v_flag;
	unsigned int	nb_players;
	unsigned int	nb_procs;
	unsigned int	id_counter;
	t_process		*proc_list;
	struct s_visu	*visu;
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

typedef struct		s_attr
{
	int				owner;
}					t_attr;

typedef struct		s_visu
{
	WINDOW			*arena;
	WINDOW			*side1;
	WINDOW			*side2;
	WINDOW			*side3;
	WINDOW			*side4;
	t_attr			attr_arena[MEM_SIZE];
}					t_visu;

/*
**					VM FUNCTIONS
*/

void				init_vm(t_vm *vm);
void				run_cycles(t_vm *vm);
void				init_arena(t_vm *vm, t_arena *arena);
void				print_arena(t_arena *arena);
void				dump_memory(t_vm *vm);

/*
**					HELPER FUNCTIONS
*/

void				ft_errno(char *id);
void				get_op(t_op *op);
int					validate_encoding(t_vm *vm, int encode_byte,
					t_process *proc);
void				free_all(t_vm *vm);
void				*assign_opfunctions(int opcode);
int					get_addr(int addr);
int					get_args(t_vm *vm, t_process *proc);
void				remove_proc(t_vm *vm, t_process **proc_list,
					t_process **current, t_process **previous);
int					int_arg(t_vm *vm, int idx);
int					get_op_values(t_vm *vm, t_process *proc, int arg);
void				load_into_memory(t_vm *vm, unsigned int addr,
					void *content);
void				init_processes(t_vm *vm);
void				decleare_winner(t_vm *vm);
void				add_to_list(t_process *new, t_process **list);
t_process			*new_proc();
t_process			*copy_proc(t_vm *vm, t_process *og_proc);

/*
**					PARSE INPUT FUNCTIONS
*/

int					validate_chapions(char **s);
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

void				start_visualizer(t_vm *vm);
void				define_colors(void);
int					get_attribute(t_vm *vm, int idx);
void				draw_arena(t_vm *vm);
void				draw_players(t_vm *vm);
void				draw_logo(t_vm *vm);
void				draw_battle_info(t_vm *vm);
void				draw_footer(t_vm *vm);
void				print_winner(t_vm *vm);
void				box_win(WINDOW *win);
void 				print_player1(t_vm *vm, int height, int weidth);
void 				print_player2(t_vm *vm, int height, int weidth);
void 				print_player3(t_vm *vm, int height, int weidth);
void 				print_player4(t_vm *vm, int height, int weidth);
void				print_info(t_vm *vm, t_player *player, int y, int x);
void				print_player_info(t_vm *vm);
void				init_visualizer(t_vm *vm);

static const t_op			g_ops[16] = {
	{
		.instr_name = "live",
		.argc = 1,
		.argv = {T_DIR, 0, 0},
		.instr_code = 1,
		.wait_cycles = 10,
		.dir_size = 4,
		.encode = 0,
		.f = op_live
	},
	{
		.instr_name = "ld",
		.argc = 2,
		.argv = {T_DIR | T_IND, T_REG, 0},
		.instr_code = 2,
		.wait_cycles = 5,
		.dir_size = 4,
		.encode = 1,
		.f = op_ld
	},
	{
		.instr_name = "st",
		.argc = 2,
		.argv = {T_REG, T_IND | T_REG, 0},
		.instr_code = 3,
		.wait_cycles = 5,
		.dir_size = 4,
		.encode = 1,
		.f = op_st
	},
	{
		.instr_name = "add",
		.argc = 3,
		.argv = {T_REG, T_REG, T_REG},
		.instr_code = 4,
		.wait_cycles = 10,
		.dir_size = 4,
		.encode = 1,
		.f = op_add
	},
	{
		.instr_name = "sub",
		.argc = 3,
		.argv = {T_REG, T_REG, T_REG},
		.instr_code = 5,
		.wait_cycles = 10,
		.dir_size = 4,
		.encode = 1,
		.f = op_sub
	},
	{
		.instr_name = "and",
		.argc = 3,
		.argv = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.instr_code = 6,
		.wait_cycles = 6,
		.dir_size = 4,
		.encode = 1,
		.f = op_and
	},
	{
		.instr_name = "or",
		.argc = 3,
		.argv = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.instr_code = 7,
		.wait_cycles = 6,
		.dir_size = 4,
		.encode = 1,
		.f = op_or
	},
	{
		.instr_name = "xor",
		.argc = 3,
		.argv = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.instr_code = 8,
		.wait_cycles = 6,
		.dir_size = 4,
		.encode = 1,
		.f = op_xor,
	},
	{
		.instr_name = "zjmp",
		.argc = 1,
		.argv = {T_DIR, 0, 0},
		.instr_code = 9,
		.wait_cycles = 20,
		.dir_size = 2,
		.encode = 0,
		.f = op_zjmp
	},
	{
		.instr_name = "ldi",
		.argc = 3,
		.argv = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.instr_code = 10,
		.wait_cycles = 25,
		.dir_size = 2,
		.encode = 1,
		.f = op_ldi
	},
	{
		.instr_name = "sti",
		.argc = 3,
		.argv = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.instr_code = 11,
		.wait_cycles = 25,
		.dir_size = 2,
		.encode = 1,
		.f = op_sti
	},
	{
		.instr_name = "fork",
		.argc = 1,
		.argv = {T_DIR, 0, 0},
		.instr_code = 12,
		.wait_cycles = 800,
		.dir_size = 2,
		.encode = 0,
		.f = op_fork
	},
	{
		.instr_name = "lld",
		.argc = 2,
		.argv = {T_DIR | T_IND, T_REG, 0},
		.instr_code = 13,
		.wait_cycles = 10,
		.dir_size = 4,
		.encode = 1,
		.f = op_lld
	},
	{
		.instr_name = "lldi",
		.argc = 3,
		.argv = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.instr_code = 14,
		.wait_cycles = 50,
		.dir_size = 2,
		.encode = 1,
		.f = op_lldi
	},
	{
		.instr_name = "lfork",
		.argc = 1,
		.argv = {T_DIR, 0, 0},
		.instr_code = 15,
		.wait_cycles = 1000,
		.dir_size = 2,
		.encode = 0,
		.f = op_lfork
	},
	{
		.instr_name = "aff",
		.argc = 1,
		.argv = {T_REG, 0, 0},
		.instr_code = 16,
		.wait_cycles = 2,
		.dir_size = 4,
		.encode = 1,
		.f = op_aff
	}
};

#endif
