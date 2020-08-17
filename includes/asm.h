/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:05:18 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/12 16:55:53 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** Header file used by open
*/

# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "printf.h"
# include "op.h"

/*
** Defines for different token types.
** Note that ARG_LABEL is only a mask for dir and indir labels
** and not an actual token type.
*/

# define REGISTER T_REG
# define DIRECT T_DIR
# define INDIRECT T_IND
# define INSTRUCTION 8
# define LABEL 16
# define SEPARATOR 32
# define STRING 64
# define CMD_STR 128
# define ARG_LABEL 256
# define DIRECT_LABEL 258
# define INDIRECT_LABEL 260
# define ENDLINE 512
# define COMMAND_NAME 1152
# define COMMAND_COMMENT 2176

# define MALLOC_ERROR "Malloc error"

# define SYNTAX_ERROR 1
# define INVALID_INSTR 2

# define NUMBER -1

/*
** T_cursor
** The current location row and column
*/

typedef struct	s_cursor
{
	int	row;
	int	col;
}				t_cursor;

/*
** T_arg
** Type: Either T_REG, T_IND or T_DIR
** Size: Size of argument in bytes
*/

typedef struct	s_arg
{
	int			type;
	char		*content;
	int			size;
	t_cursor	*cursor;
}				t_arg;

/*
** T_stmt (statement)
** Name: Command name, for example "live" or "sti"
** Args: Args[0] will be the first argument, args[MAX_ARGS_NUMBER - 1] is null.
**       If there are less than MAX_ARGS_NUMBER - 1 arguments, pad with null.
** Size: Statement code size + argument sizes in bytes
** Place: Iterator place. For example for the first stament, this value will be
**        0. If the 1st statement size is 7, this value will be 7 for the second
**        argument.
*/

typedef struct	s_stmt
{
	char			*name;
	t_arg			*args[MAX_ARGS_NUMBER];
	int				size;
	int				place;
	struct s_stmt	*next;
	int				arg_code;
	int				instr_code;
}				t_stmt;

/*
** T_label
** Place: The statement location the label points to
*/

typedef struct	s_label
{
	char			*name;
	int				place;
	struct s_label	*next;
}				t_label;

/*
** T_champ
** Done: Indicates if the champion values name and comment have been saved
*/

typedef struct	s_champ
{
	char	*name;
	char	*comment;
	int		done;
	t_label	*labels;
	t_stmt	*stmts;
}				t_champ;

/*
** T_token
** Contains information on each .s file component
** Example line: .name "Matti"
** token 1: | type: COMMAND_NAME | content: .name   | cursor: [row 1 col 0] |
** token 2: | type: STRING  | content: "Matti" | cursor: [row 1 col 6] |
*/

typedef struct	s_token
{
	int				type;
	char			*content;
	t_cursor		*cursor;
	struct s_token	*next;
}				t_token;

typedef struct	s_op
{
	char		*instr_name;
	int			argc;
	int			*argv;
	int			instr_code;
	struct s_op	*next;
}				t_op;

/*
** T_asm
** Contains lists and other important information needed in this project
** Tokens: A list of all the tokens
** Champ: Champion name, comment, labels and statements (a list of all the
** statements)
*/

typedef struct	s_asm
{
	t_op		*op;
	t_token		*tokens;
	t_champ		champ;
}				t_asm;

int				overlap(int type1, int type2);
void			parse_file(int fd, t_asm *assembler);
int				is_valid_char(char c);
void			validate_characters(char *line, int col, int row,
				int *end_point);
int				validate_number(char *line, int start, t_cursor cursor);
int				validate_cmd_str(char *line, t_cursor cursor);
int				skip_whitespaces(char *line, int i);
int				skip_valid_chars(char *line, int i);
t_token			*tokenize(char *line, t_cursor cursor, char *edge_chars);
int				find_first_char(char *str, int start, char *chars);
int				find_last_char(char *str, int start, char *chars);
char			*add_str_to_str(char *s1, char *s2);
void			handle_error(char *msg);
void			check_args(int ac, char **av);
void			lexical_error(t_cursor cursor);
void			check_for_lexical_error(char *line, t_cursor cursor,
				int *token_end, char *edge_chars);
int				ft_isnum(char *str);
int				asm_gnl(const int fd, char **line);
int				count_string_chars(char *str);
t_op			*get_op(void);
void			make_cor_file(char *s_filename, t_asm assembler);
void			check_token_order(t_token *token);
char			*pad_nbr(int nbr, int size);
char			*token_type_str(int type);
int				find_first_str(char *haystack, int start, char *needle);
char			*add_strs_to_str(char *str, char **strs);
char			*join_free_strs(char *s1, char *s2);
void			del_array(char **array);
void			handle_error_msg(int error, t_token *token);
void			check_token_validity(t_token *token, t_op *op);
void			check_statement_order(t_token *token, t_champ *champ);
void			insert_bytes_number(int fd, int nbr, int size);
void			insert_bytes_string(int fd, char *str, int size);
void			init_champ(t_champ *champ);
void			set_champ(t_champ *champ, t_token *token);
void			insert_statements(t_stmt *stmt, t_label *labels,
				t_op *op, int fd);
int				get_arg_code(t_stmt *stmt);
int				convert_dec(char *binary, int size);
char			*make_rev_binary_str(int nbr);
t_cursor		*copy_cursor(t_cursor cursor);
void			labels_to_rel_adrs(t_label *labels, t_stmt *stmt);
void			handle_invalid_label(t_arg *arg, char *label_name);
char			*copy_string_content(char *string);
void			check_str_len(char *name, char *comment);

#endif
