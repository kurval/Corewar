/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:05:18 by jmetelin          #+#    #+#             */
/*   Updated: 2020/07/29 17:05:22 by jmetelin         ###   ########.fr       */
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

/*
** T_champ
** Done: Indicates if champion values have been saved
*/

typedef struct	s_champ
{
	char	*name;
	char	*message;
	int		done;
	char	*code;
}				t_champ;

/*
** T_argument
** Type: Either T_REG, T_IND or T_DIR
** Content: Might have to change this later - not sure if it works
** Size: Size of argument in bytes
*/

typedef struct	s_argument
{
	int		type;
	void	*content;
	int		size;
}				t_argument;

/*
** T_statement
** Name: Command name, for example "live" or "sti"
** Args: Args[0] will be the first argument, args[MAX_ARGS_NUMBER - 1] is null.
**       If there are less than MAX_ARGS_NUMBER -1 arguments, pad with null.
** Size: Statement code size + argument sizes in bytes
** Place: Iterator place. For example for the first stament, this value will be
**        0. If the 1st statement size is 7, this value will be 7 for the second
**        argument.
*/

typedef struct	s_statement
{
	int					code;
	char				*name;
	t_argument			args[MAX_ARGS_NUMBER];
	int					size;
	int					place;
	struct s_statement	*next;
}				t_statement;

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

typedef struct	s_cursor
{
	int	row;
	int	col;
}				t_cursor;

typedef struct	s_token
{
	int				type;
	char			*content;
	t_cursor		*cursor;
	struct s_token	*next;
}				t_token;

int				overlap(int type1, int type2);
void			parse_file(int fd);
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
char			*merge_strs(char *s1, char *s2);
void			handle_error(char *msg);
void			check_params(int ac, char **av);
void			lexical_error_tmp(t_cursor cursor);
void			check_for_lexical_error(char *line, t_cursor cursor,
				int *token_end, char *edge_chars);
int				ft_isnum(char *str);
int				asm_gnl(const int fd, char **line);
int				count_string_chars(char *str);
#endif
